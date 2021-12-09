import sys
from io import BytesIO
import requests

from flask import Flask, json, request, abort

from PIL import Image

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process_img():
    image_uri: str = request.data
    if not image_uri:
        abort(400)

    try:
        response = requests.get(image_uri.strip())
    except:
        abort(400)
    try:
        img = Image.open(BytesIO(response.content)).resize((16,16), Image.ANTIALIAS)

        if len(img.split()) == 4:
            # prevent IOError: cannot write mode RGBA as BMP
            r, g, b, a = img.split()
            img = Image.merge("RGB", (r, g, b))

        rgb_img = img.convert("RGB")
        w, h = img.size
        px = rgb_img.load()
        out = ""
        for x in range(h):
            for y in range(w):
                r, g, b = px[x,y]
                out += f"{r} {g} {b} "
        return out
    except Exception as ex:
        abort(500, {"message": ex})
