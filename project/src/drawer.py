from PIL import Image, ImageDraw

im = None
draw = None

def createImage(width, height):
    global im, draw
    im = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(im)

def drawRectangle(startX, startY, endX, endY, color):
    draw.rectangle((startX, startY, endX, endY), fill=color)

def drawLine(startX, startY, endX, endY, color):
    draw.line((startX, startY, endX, endY), fill=color)

def drawCircle(centerX, centerY, radius, color):
    startX = centerX - radius
    startY = centerY - radius
    endX = centerX + radius
    endY = centerY + radius
    draw.ellipse((startX, startY, endX, endY), fill=color)

def drawText(x, y, text, color):
    draw.text((x, y), text, fill=color)

def saveImage(filename):
    im.save(filename)
#
# #     from drawer import *
#     createImage(600, 400)
#     # Its starting upper-left point is (10, 20)
#     # Its finishing bottom-right point is (100, 130)
#     drawRectangle(10, 20, 100, 130, (255,0,0))
#     drawLine(60, 80, 65, 280, (0, 0, 150))
#     # Its radius is 84
#     drawCircle(200, 250, 84, (10, 200, 150))
#     # Save the image with filename "myart.png"
#     saveImage("myart.png")
