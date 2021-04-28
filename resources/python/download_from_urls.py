import sys
import os
import requests

url_file = os.path.join(os.path.dirname(__file__), "urls.txt")

total_num = 0
with open(url_file, "r") as f:
    lines = f.readlines()
    print("num lines : ", len(lines))
    total_num = len(lines)


for i, line in enumerate(lines):
    url = line.rstrip()
    print(i+1, '/', total_num, url)

    res = requests.get(url)

    print(res.status_code)
    if(res.status_code == 200):
        (dir, file_name) = os.path.split(url)

        out_file = os.path.join("D:\DEM_files", file_name)
        with open(out_file, "wb") as f:
            f.write(res.content)
    else:
        print('error downloading file')
