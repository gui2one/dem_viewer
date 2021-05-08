import os
import json
hgt_files = []

dir_path = "D:\\DEM_files\\"
for root, dirs, files in os.walk(dir_path):
    for file in files:
        if file.endswith(".hgt"):
            hgt_files.append(os.path.join(root, file))
            # print(os.path.join(root, file))


# with open(os.path.join(os.path.dirname(__file__), "hgt_files_list.txt"), "w") as f:
#     for file_path in hgt_files:
#         f.write(file_path)
#         f.write("\n")


output = json.dumps(hgt_files)
print(output)