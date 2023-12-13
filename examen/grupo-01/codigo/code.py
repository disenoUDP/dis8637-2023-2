# SPDX-FileCopyrightText: 2019 Kattni Rembor for Adafruit Industries
# SPDX-License-Identifier: MIT

# Circuit Playground notitas
import time
import board
import touchio
import digitalio

from audiocore import WaveFile
try:
    from audioio import AudioOut
except ImportError:
    try:
        from audiopwmio import PWMAudioOut as AudioOut
    except ImportError:
        pass

bpm = 1  # Beats por minuto

# encender el altavoz!
speaker_enable = digitalio.DigitalInOut(board.SPEAKER_ENABLE)
speaker_enable.direction = digitalio.Direction.OUTPUT
speaker_enable.value = True

#que funcionen los touchs
touch_A1 = touchio.TouchIn(board.A1)
touch_A2 = touchio.TouchIn(board.A2)
touch_A3 = touchio.TouchIn(board.A3)
touch_A4 = touchio.TouchIn(board.A4)
touch_A5 = touchio.TouchIn(board.A5)

# los _5_ nombres de los archivos de sonido externos
audiofiles = ["Do Bajo.wav", "Mi M.wav", "Sol M.wav",
              "Mi menor.wav", "Do Alto.wav"]

audio = AudioOut(board.SPEAKER)

touch_pads = [touch_A1, touch_A2, touch_A3, touch_A4, touch_A5]

def play_file(filename):
    print("tocando notita " + filename)
    with open(filename, "rb") as file:
        wave = WaveFile(file)
        audio.play(wave)
        time.sleep(bpm / 2)  # delay de notas :)
while True:
    for i in range(5):
        if touch_pads[i].value:
            play_file(audiofiles[i])

    time.sleep(0.01)
