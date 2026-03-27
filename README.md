🩺 AayuGuide: AI-Powered Handheld Medical Assistant
AayuGuide is an intelligent, handheld diagnostic device designed to provide instant health insights. By combining the power of Google Gemini AI with real-time vitals monitoring (Non-contact Temperature), AayuGuide allows users to speak their symptoms, measure their fever, and receive AI-driven medical guidance both visually and via voice.
🚀 Key Features
🎙️ Voice-to-AI Interaction: Speak symptoms directly into the device using the I2S microphone.
🌡️ Non-Contact Thermometer: Integrated MLX90614 sensor measures body temperature instantly.
🔊 Voice Response: AI advice is read aloud via an I2S Audiophile-grade DAC and speaker.
🖥️ Visual UI: A 3.2" TFT LCD shows symptoms, temperature readings, and AI suggestions.
🔋 Fully Portable: Powered by a 3.7V LiPo battery with integrated charging and 5V boost conversion.
🧠 Cloud-Brain: Connected to a FastAPI server running Google Gemini Pro for advanced medical reasoning.
🛠️ Hardware Architecture
Core Components
Component	Function	Interface
ESP32 38-Pin NodeMCU	Main Controller (WiFi/BT)	MCU
3.2" TFT LCD (ILI9341)	Visual Interface & Touch	SPI
MLX90614ESF	Infrared Medical Temperature Sensor	I2C
INMP441	High-performance MEMS Microphone	I2S (Input)
MAX98357A	I2S Amp & DAC for Speaker	I2S (Output)
TTP223	Capacitive Touch Sensor (Trigger/Power)	Digital
MT3608	2A Step-Up (3.7V to 5V)	Power
TP4056	LiPo Charging Module with Protection	Power
3.7V LiPo	Portable Power Source	Power
🔌 Pin Mapping (ESP32 38-Pin)
Component	ESP32 Pin (GPIO)	Connection Type
TFT LCD	SCK(18), MISO(19), MOSI(23), CS(5), DC(2), RST(4)	SPI
INMP441 (Mic)	WS(25), SCK(26), SD(33)	I2S Input
MAX98357A (Amp)	LRCK(27), BCLK(14), DIN(12)	I2S Output
MLX90614 (Temp)	SDA(21), SCL(22)	I2C
TTP223 (Button)	GPIO 32	Digital Input
💻 Software Stack
Firmware: Written in C++ using the Arduino IDE / PlatformIO.
Libraries: TFT_eSPI (Display), Adafruit_MLX90614 (Temp), Audio.h (I2S Sound).
Backend: FastAPI (Python) hosted on Google Cloud Shell / Render.
AI Model: Google Gemini Pro API (for symptom analysis and medical advice).
📂 System Flow
Input: User touches the TTP223 sensor and speaks symptoms.
Sensing: The MLX90614 takes a temperature reading simultaneously.
Processing: The ESP32 sends the voice data and temperature to the FastAPI Server.
AI Reasoning: The server queries Gemini Pro, asking it to analyze the symptoms + temperature.
Output: The AI response is sent back; the ESP32 displays the text on the 3.2" Screen and plays the audio via the MAX98357A.
