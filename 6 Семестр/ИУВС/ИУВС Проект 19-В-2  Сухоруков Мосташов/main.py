from flask import Flask, render_template, request, g, flash, redirect
from datetime import datetime
import sqlite3
import os
from Source.FDataBase import *
from Source.Sensors import *

# Конфигурация
DATABASE = 'flsite.db'
SECRET_KEY = 'bniubiht5698088%^%*%*njjgi'
DEBUG = True

app = Flask(__name__)
app.config.from_object(__name__)
_current_un = int(0)

app.config.update(dict(DATABASE=os.path.join(app.root_path, 'flsite.db')))


def connect_db():
    conn = sqlite3.connect(app.config['DATABASE'])
    conn.row_factory = sqlite3.Row
    return conn


def create_db():
    db = connect_db()
    with app.open_resource('sq_db.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()
    db.close()


def get_db():
    if not hasattr(g, 'link_db'):
        g.link_db = connect_db()
    return g.link_db


def create_sensors():
    ir_1 = IRSensor(1)
    ir_2 = IRSensor(2)
    ir_3 = IRSensor(3)

    vibr_1 = VibrationSensor(1)
    vibr_2 = VibrationSensor(2)
    vibr_3 = VibrationSensor(3)

    magn_1 = MagneticContactSensor(1)
    magn_2 = MagneticContactSensor(2)
    magn_3 = MagneticContactSensor(3)

    sensors = (ir_1, ir_2, ir_3, vibr_1, vibr_2, vibr_3, magn_1, magn_2, magn_3)

    return sensors


def get_sensors():
    if not hasattr(g, 'sensors'):
        g.sensors = create_sensors()
    return g.sensors


@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'link_db'):
        g.link_db.close()


@app.route("/")
def index_get():
    return render_template('index.html', UN=_current_un)


@app.route("/", methods=['POST'])
def index_post():
    db = get_db()
    dbase = FDataBase(db)
    un = request.form['UN']
    tmp = dbase.get_by_number(un)

    if tmp != False:
        global _current_un
        _current_un = un
        na = tmp['Name']
        sna = tmp['Surname']
        st = tmp['status']
        f = tmp['Foto']
        t = datetime.now()
        dbase.add_entery(un, na, sna, st, f, 'Зашёл', t)
        foto = '/static/image/'+f
        flash('Успешный вход ', category='success')
        return render_template('profile.html', UN=un, Status=st, Name=na, Surname=sna,Foto=foto)
    else:
        flash('Ошибка входа ', category='error')
        return render_template('index.html', UN=0)


@app.route("/profile/<int:un>")
def profile(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    na = res['Name']
    sna = res['Surname']
    st = res['Status']
    f = '/static/image/'+res['Foto']
    return render_template('profile.html', UN=un, Status=st, Name=na, Surname=sna, Foto=f)


@app.route("/profile")
def profile_1():
    global _current_un
    un = _current_un
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    na = res['Name']
    sna = res['Surname']
    st = res['Status']
    f = '/static/image/'+res['Foto']
    return render_template('profile.html', UN=un, Status=st, Name=na, Surname=sna, Foto=f)


@app.route("/out/<int:un>")
def out(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    na = res['Name']
    sna = res['Surname']
    st = res['Status']
    f = res['Foto']
    t = datetime.now()
    dbase.add_entery(un, na, sna, st, f, 'Вышел', t)
    return redirect('/')


@app.route("/add_number/<int:un>")
def add_number_get(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    status = res['Status']
    if status =="работник отдела кадров":
        return render_template('add_number.html', UN=un)
    else:
        flash('У вас нет доступа к добавлению новых работников', category='error')
        global _current_un
        _current_un = un
        return redirect('/profile')


@app.route("/add_number/<int:un>", methods=["POST"])
def add_number_post(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    status = res['Status']
    if status =="работник отдела кадров":
        UN = request.form['UN']
        Name = request.form['Name']
        Surname = request.form['Surname']
        Foto = request.form['Foto']
        Status = request.form['Status']
        res = dbase.add_number(UN, Name, Surname, Foto, Status)
        if not res:
            flash('Ошибка добавления ', category='error')
        else:
            flash('Успешное добавление ', category='success')
        return render_template('add_number.html', UN=un)
    else:
        flash('У вас нет доступа к добавлению новых работников', category='error')
        global _current_un
        _current_un = un
        return redirect('/profile')


@app.route("/sensors/<int:un>")
def sensors(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    status = res['Status']
    if status =="работник охраны":
        sen = get_sensors()
        sen_db = dbase.get_disturbance()
        type = list()
        id = list()
        time = list()
        for d in sen_db:
            type.append(d['Type'])
            id.append(d['number'])
            time.append(d['Time'])
        length = len(id)

        return render_template('Sensors.html', UN=un, Sensors=sen,Type=type, Time=time, ID=id, LEN=length)
    else:
        flash('У вас нет доступа к показаниям датчиков', category='error')
        global _current_un
        _current_un = un
        return redirect('/profile')


@app.route("/sensors/<int:un>", methods=["POST"])
def sensors_post(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    status = res['Status']
    if status =="работник охраны":
        sen = get_sensors()
        for s in sen:
            s.install_state()
            if s.status == 'Обнаружено нарушение':
                t = datetime.now()
                dbase.add_disturbance(s.type, s.id,t)

        sen_db = dbase.get_disturbance()
        type = list()
        id = list()
        time = list()
        for d in sen_db:
            type.append(d['Type'])
            id.append(d['number'])
            time.append(d['Time'])
        length = len(id)

        return render_template('Sensors.html', UN=un, Sensors=sen, Type=type, Time=time, ID=id, LEN=length)
    else:
        flash('У вас нет доступа к показаниям датчиков', category='error')
        global _current_un
        _current_un = un
        return redirect('/profile')


@app.route("/enters/<int:un>")
def enters(un):
    db = get_db()
    dbase = FDataBase(db)
    res = dbase.get_by_number(un)
    status = res['Status']
    if status =="работник охраны":
        Data = dbase.get_enters_db()
        en = list()
        sna = list()
        na = list()
        foto = list()
        time = list()
        for d in Data:
            en.append(d['Entry'])
            sna.append(d['Surname'])
            na.append(d['Name'])
            foto.append('/static/image/'+d['Foto'])
            time.append(d['Time'])
        length = len(en)
        return render_template('enters.html', UN=un, EN=en, Sna=sna, Name=na, Foto=foto, Time=time, LEN=length)
    else:
        flash('У вас нет доступа к данным пропусконого пункта', category='error')
        global _current_un
        _current_un = un
        return redirect('/profile')


@app.route("/allert/<int:un>")
def allert(un):
    return render_template('allert.html', UN=un)


@app.route("/allert/<int:un>", methods=["POST"])
def allert_post(un):
    db = get_db()
    dbase = FDataBase(db)
    t = datetime.now()
    dbase.add_disturbance('Кнопка тревоги', int(1), t)
    global _current_un
    _current_un = un
    flash('Сработала кнопка тревоги', category='error')
    return redirect('/profile')

create_db()


if __name__ == "__main__":
    app.run()
    app.run()
