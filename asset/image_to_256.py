from PIL import Image
import numpy as np

# 打开图像文件
img = Image.open('input.png')

# 调整图像大小到128x128
img = img.resize((128, 128))

# 将图像转换为RGB格式
img = img.convert('RGB')

# 转换为numpy数组
img_array = np.array(img)

# 将数组展平成一维数组
c_array = img_array.flatten()

# 生成C语言数组字符串
c_array_string = ',\n'.join(map(str, c_array))
c_code = f"unsigned char SIZE_128x128[] = {{\n{c_array_string}}};\n"

# 将结果写入.c文件
with open('..\\src\\applications\\output.c', 'w') as file:
    file.write(c_code)

print("C array has been written to output.c")

