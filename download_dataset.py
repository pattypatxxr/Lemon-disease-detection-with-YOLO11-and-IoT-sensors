# !pip install roboflow

from roboflow import Roboflow
rf = Roboflow(api_key="BBrEcKC0exPFA7SVBLpo")
project = rf.workspace("torpat-rnkue").project("lemon-leaf-disease-o6qho")
version = project.version(1)
dataset = version.download("folder")
                