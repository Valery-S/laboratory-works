import random

class Sensor:
    def __init__(self):
        self.status = "Нарушений не обнаружено"

    def install_state(self):
        number = random.random()  # значение от 0.0 до 1.0
        if number > 0.95 or number < 0.05:
            self.status = "Обнаружено нарушение"


class IRSensor(Sensor):
    def __init__(self, identifier):
        self.status = "Нарушений не обнаружено"
        self.type = "Инфракрасный датчик"
        self.id = identifier


class VibrationSensor(Sensor):
    def __init__(self, identifier):
        self.status = "Нарушений не обнаружено"
        self.type = "Вибрационный датчик"
        self.id = identifier


class MagneticContactSensor(Sensor):
    def __init__(self, identifier):
        self.status = "Нарушений не обнаружено"
        self.type = "Магнитоконтактный датчик"
        self.id = identifier

