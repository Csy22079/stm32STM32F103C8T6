from board import board_info
from fpioa_manager import fm
from machine import UART
from maix import GPIO
import time
import lcd
import sensor
import gc
from maix import KPU

# 初始化串口 2
uart1 = UART(UART.UART1, 115200)
uart2 = UART(UART.UART2, 115200)


fm.register(board_info.EX_UART1_TX, fm.fpioa.UART1_TX)
fm.register(board_info.EX_UART1_RX, fm.fpioa.UART1_RX)
fm.register(board_info.EX_UART2_TX, fm.fpioa.UART2_TX)
fm.register(board_info.EX_UART2_RX, fm.fpioa.UART2_RX)

fm.register(board_info.KEY0, fm.fpioa.GPIOHS0)
key0 = GPIO(GPIO.GPIOHS0, GPIO.IN, GPIO.PULL_UP)

fm.register(board_info.EX_IO5, fm.fpioa.GPIO5)
# 构造GPIO对象
facesta = GPIO(GPIO.GPIO5, GPIO.OUT)



# 注册 key1 引脚
fm.register(board_info.KEY1, fm.fpioa.GPIOHS1)  # 假设 KEY1 对应 GPIOHS1，根据实际情况修改
key1 = GPIO(GPIO.GPIOHS1, GPIO.IN, GPIO.PULL_UP)

delete_all_features = False  # 新增标志位，用于标记是否要删除所有特征

save_feature = False
def key_irq_handler(key):
    global key0
    global save_feature
    time.sleep_ms(20)
    if key is key0 and key.value() == 0:
        save_feature = True
key0.irq(key_irq_handler, GPIO.IRQ_FALLING, GPIO.WAKEUP_NOT_SUPPORT, 7)


def key1_irq_handler(key):
    global key1
    global delete_all_features
    time.sleep_ms(20)
    if key is key1 and key.value() == 0:
        delete_all_features = True

key1.irq(key1_irq_handler, GPIO.IRQ_FALLING, GPIO.WAKEUP_NOT_SUPPORT, 7)

lcd.init()
sensor.reset()
sensor.set_framesize(sensor.QVGA)
sensor.set_pixformat(sensor.RGB565)
sensor.set_vflip(False)

anchor = (0.1075, 0.126875, 0.126875, 0.175, 0.1465625, 0.2246875, 0.1953125, 0.25375, 0.2440625, 0.351875, 0.341875, 0.4721875, 0.5078125, 0.6696875, 0.8984375, 1.099687, 2.129062, 2.425937)
names = ['face']

# 构造并初始化人脸检测KPU对象
face_detecter = KPU()
face_detecter.load_kmodel("/sd/face_detect_320x240.kmodel")
face_detecter.init_yolo2(anchor, anchor_num=len(anchor) // 2, img_w=320, img_h=240, net_w=320, net_h=240, layer_w=10, layer_h=8, threshold=0.5, nms_value=0.2, classes=len(names))

features = []
score_threshold = 80


# 列出所有板卡信息
info = board_info.all()[8:]
print(*info, sep='\n', end='\n\n')

# 构造并初始化人脸特征提取KPU对象
feature_extractor = KPU()
feature_extractor.load_kmodel('/sd/feature_extraction.kmodel')


# 按指定比例扩展矩形框
def extend_box(x, y, w, h, scale):
    x1 = int(x - scale * w)
    x2 = int(x + w - 1 + scale * w)
    y1 = int(y - scale * h)
    y2 = int(y + h - 1 + scale * h)
    x1 = x1 if x1 > 0 else 0
    x2 = x2 if x2 < (320 - 1) else (320 - 1)
    y1 = y1 if y1 > 0 else 0
    y2 = y2 if y2 < (240 - 1) else (240 - 1)
    return x1, y1, x2 - x1 + 1, y2 - y1 + 1
facesta.value(1)
uart1.write('1')#开锁
uart2.write('1')#开锁
while True:
    img = sensor.snapshot()
    face_detecter.run_with_output(img)
    faces = face_detecter.regionlayer_yolo2()
    # 默认状态下输出高电平（没有检测到人脸或检测到其他人脸）
    facesta.value(1)
    uart2.write('0')
    for face in faces:
        # 框出人脸位置
        x, y, w, h = extend_box(face[0], face[1], face[2], face[3], 0.08)
        img.draw_rectangle(x, y, w, h, color=(0, 255, 0))
        # 计算人脸特征并于保存的人脸特征进行比对获取相似度得分
        scores = []
        max_score = 0
        face_img = img.cut(x, y, w, h)
        resize_img = face_img.resize(64, 64)
        resize_img.pix_to_ai()
        feature = feature_extractor.run_with_output(resize_img, get_feature=True)
        for i in range(len(features)):
            score = KPU.feature_compare(features[i], feature)
            scores.append(score)
        # 计算得分的最大值
        if len(scores) is not 0:
            max_score = max(scores)
        else:
            facesta.value(1)
            uart1.write('0')#
            uart2.write('0')
        # 根据阈进行人脸识别
        if max_score > score_threshold:
            img.draw_rectangle(x, y, w, h, color=(0, 255, 0))
            img.draw_string(x + 2, y + 2, str(scores.index(max(scores))), color=(0, 255, 0), scale=1.5)
            # 识别到录入的人脸，输出100ms低电平然后恢复高电平
            facesta.value(0)
            time.sleep_ms(100)
            facesta.value(1)
            uart1.write('1')#开锁
            uart2.write('1')#开锁
        else:
            # 识别到其他人脸，输出高电平
            facesta.value(1)
            uart1.write('2')#开锁
            uart2.write('2')#陌生人
        # 根据中断按键进行人脸特征录入
        if save_feature is True:
            save_feature = False
            features.append(feature)
             # 根据中断按键进行删除所有特征操作
        if delete_all_features is True:
            delete_all_features = False
            features = []  # 清空特征列表
        del scores
        del max_score
        del face_img
        del resize_img
        del feature
    lcd.display(img)
    gc.collect()
