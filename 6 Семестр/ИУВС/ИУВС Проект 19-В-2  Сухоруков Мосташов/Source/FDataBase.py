import sqlite3

class FDataBase:
    def __init__(self, db):
        self.__db = db
        self.__cur = db.cursor()

    def get_by_number(self, un):
        try:
            self.__cur.execute("select * from unique_number where UN=:un", {"un": un})
            res = self.__cur.fetchone()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения информации о сотруднике"+str(e))
        return False

    def get_enters_db(self):
        try:
            self.__cur.execute("select * from Enters ")
            res = self.__cur.fetchall()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения данных пропускного пункта"+str(e))
        return False

    def get_disturbance(self):
        try:
            self.__cur.execute("select * from Disturbance ")
            res = self.__cur.fetchall()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения данных датчиков"+str(e))
        return False

    def add_number(self, UN, Name, Surname, Foto, Status):
        try:
            self.__cur.execute("INSERT INTO unique_number VALUES(NULL,?, ?, ?, ?,?)",
                               (UN, Name, Surname, Status,Foto))
            self.__db.commit()
        except sqlite3.Error as e:
            print("Ошибка добавления" + str(e))
            return False
        return True

    def add_entery (self, un, na, sna, st, f, entry,t):
        try:
            self.__cur.execute("INSERT INTO Enters VALUES(NULL,?, ?, ?, ?,?,?,?)",
                               (entry, un, na, sna, st, f, t))
            self.__db.commit()
        except sqlite3.Error as e:
            print("Ошибка добавления " + str(e))
            return False
        return True

    def add_disturbance (self, type, number, time):
        try:
            self.__cur.execute("INSERT INTO Disturbance VALUES(NULL,?, ?,?)",
                               (type, number, time))
            self.__db.commit()
        except sqlite3.Error as e:
            print("Ошибка добавления " + str(e))
            return False
        return True
