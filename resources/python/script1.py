import os
import sys
import json

root_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0,os.path.join(root_dir, "modules"))
from PIL import Image

print(dir(Image))
print(Image.Image)


# print(dir(Image))
# print(Image)
print(root_dir)