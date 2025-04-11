import pandas as pd
from PIL import Image, ImageDraw, ImageFont

# Test

OUTPUT_PATH = r"output.png"
CSV_PATH = r"risk/float.csv"
SYS_NAME = "漂浮系統"
SYS_FUNCTION_1 = "使火箭降落後可"
SYS_FUNCTION_2 = "漂浮至少 10 分鐘"

IMG_SIZE = (3840, 2160)
TITLE_SIZE = 130
SUB_TITLE_SIZE = 70
TEXT_SIZE = 50

title_font = ImageFont.truetype(r"NotoSansTC-Bold.ttf", TITLE_SIZE)
sub_title_font = ImageFont.truetype(r"NotoSansTC-Bold.ttf", SUB_TITLE_SIZE)
text_font = ImageFont.truetype(r"NotoSansTC-Regular.ttf", TEXT_SIZE)
text_b_font = ImageFont.truetype(r"NotoSansTC-Bold.ttf", TEXT_SIZE)

# 讀取 CSV 檔案
df = pd.read_csv(CSV_PATH)

# 設定圖片大小
img = Image.new("RGB", IMG_SIZE, "white")
draw = ImageDraw.Draw(img)

x = 280
y = 140

# 標題
draw.text((x, y), "失效模式分析", font=title_font, fill="#1f318f")
y += TITLE_SIZE + 150

# 副標
draw.text((x, y), "系統名稱", font=sub_title_font, fill="#1f318f")
y += SUB_TITLE_SIZE + 60
draw.text((x, y), SYS_NAME, font=text_font, fill="black")
y += TEXT_SIZE + 100
draw.text((x, y), "主要功能", font=sub_title_font, fill="#1f318f")
y += SUB_TITLE_SIZE + 60
draw.text((x, y), SYS_FUNCTION_1, font=text_font, fill="black")
y += TEXT_SIZE + 10
draw.text((x, y), SYS_FUNCTION_2, font=text_font, fill="black")

# 內容
y = TITLE_SIZE + 290
x = 900
col_widths = [500, 600, 550, 450]

draw.line((800, y, 800, 2020), fill="black", width=2)

for col_idx, col_name in enumerate(df.columns):
    draw.text(
        (x + sum(col_widths[:col_idx]), y),
        col_name, font=text_font,
        fill="#1f318f"
    )

y += TEXT_SIZE + 50
draw.line((x, y, 3700, y), fill="#1f318f", width=4)

y += 40
for row_idx, row in df.iterrows():
    for col_idx, col_name in enumerate(df.columns):
        text = str(row[col_name]).split(r"\n")
        for idx, t in enumerate(text):
            draw.text(
                (x + sum(col_widths[:col_idx]), y+idx*(TEXT_SIZE+10)),
                t, font=text_font,
                fill="black"
            )
    if row_idx == len(df.columns)-1: break
    y += (TEXT_SIZE)*2 + 80
    draw.line((x, y, 3700, y), fill="black", width=2)
    y += 40
    
# 儲存圖片
img.save(OUTPUT_PATH)
print(f"圖片已儲存至 {OUTPUT_PATH}")
