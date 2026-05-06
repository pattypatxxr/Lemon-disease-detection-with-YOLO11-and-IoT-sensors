from ultralytics import YOLO

# YOLO11 classification model (pretrained)
model = YOLO("yolo11n-cls.pt")  

# Train
results = model.train(
    data="lemon_leaf-disease-1/",   # path Roboflow
        epochs=40,
        imgsz=224,
        batch=16,
        dropout=0.3,       
        patience=15, # early stopping
)       


print("Training complete!")
