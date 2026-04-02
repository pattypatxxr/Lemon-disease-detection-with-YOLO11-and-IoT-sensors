from ultralytics import YOLO

# โหลด YOLO11 classification model (pretrained)
model = YOLO("yolo11n-cls.pt")  # n = nano (เบาสุด เร็วสุด)

# Train
results = model.train(
    data="lemon-leaf-disease-1/",   # path ที่ได้จาก Roboflow
    epochs=30,
    imgsz=224,
    batch=32,
    name="lemon_disease_cls",
    patience=10        # early stopping
)

print("Training complete!")