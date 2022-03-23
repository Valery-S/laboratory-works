import tkinter as tk
import math
from PIL import Image, ImageTk
import matplotlib.pyplot as plt
import tkinter.ttk as ttk

# Списки со значениями x и y
y = []
x = []
data = []

x_max = 0.0
y_max = 0.0
x_min = 0.0
y_min = 0.0

# ------------------------------------------------------------------------------
# Нахождение значений для  x и y
# Построение графика функции y=f(x)
def get_table():
    # Очистка списков
    x.clear()
    y.clear()

    # Считывание параметров из полей ввода
    a1 = float(a1_Entry.get())
    a2 = float(a2_Entry.get())
    a3 = float(a3_Entry.get())
    b1 = float(b1_Entry.get())
    b2 = float(b2_Entry.get())
    b3 = float(b3_Entry.get())
    x0 = float(x0_Entry.get())
    dx = float(dx_Entry.get())
    xk = float(xk_Entry.get())

    # Минимальное и максимальное значение y
    x_max = x0
    y_max = a1*math.sin(b1*x0)+a2*math.sin(b2*x0)+a3*math.sin(b3+x0)

    x_min = x_max
    y_min = y_max

    i = x0
    while i <= xk:
        y_i = a1*math.sin(b1*i)+a2*math.sin(b2*i)+a3*math.sin(b3+i)
        x_i = i

        # Форматирование до 3 знаков после запятой
        x_i = float('{:.3f}'.format(x_i))
        y_i = float('{:.3f}'.format(y_i))

        # Обновление максимума и минимума
        if y_i > y_max:
            y_max = y_i
            x_max = x_i
            label_y_max['text'] = f'Ymax={y_max}'
            label_x_max['text'] = f'Xmax={x_max}'

        if y_i < y_min:
            y_min = y_i
            x_min = x_i
            label_y_min['text'] = f'Ymin={y_min}'
            label_x_min['text'] = f'Xmin={x_min}'

        # Добавление в списки
        y.append(y_i)
        x.append(x_i)
        data.append([x_i, y_i])

        i = i+dx

    # Таблица значений x и y
    table = ttk.Treeview(win)
    table['columns'] = ('X','Y')
    table.column('#0', width=0, stretch=tk.NO)
    table.column('X', anchor=tk.CENTER, width=80)
    table.column('Y', anchor=tk.CENTER, width=80)

    table.heading('#0', text='', anchor=tk.CENTER)
    table.heading('X', text='X', anchor=tk.CENTER)
    table.heading('Y', text='Y', anchor=tk.CENTER)

    for i in data:
          table.insert(parent='', index=0, values=i)

    table.place(x=260, y=350)

    # Построение графика
    plt.plot(x, y)
    plt.savefig('graph.png')
    plt.clf()

    # Отображение графика
    img = Image.open("graph.png")
    img = ImageTk.PhotoImage(img)
    graph_label = tk.Label(image=img)
    graph_label.image = img
    graph_label.place(x=670, y=20)
# -----------------------------------------------------------------------------


# Окно приложения
win = tk.Tk()
win.title('МиСОС ЛР1')
win.minsize(1280, 700)


# Основной заголовок
label_main = tk.Label(win, text='y(x)=a1*sin(b1*x)+a2*sin(b2*x)+a3*sin(b3+x)',
                      font=('Comic Sans MS', 15, 'bold'),
                      height=3,
                      relief=tk.RAISED,
                      bd=8)


# Заголовки для полей ввода
label_a1 = tk.Label(win, text='a1=', font=('Comic Sans MS', 20, 'bold'))
label_a2 = tk.Label(win, text='a2=', font=('Comic Sans MS', 20, 'bold'))
label_a3 = tk.Label(win, text='a3=', font=('Comic Sans MS', 20, 'bold'))

label_b1 = tk.Label(win, text='b1=', font=('Comic Sans MS', 20, 'bold'))
label_b2 = tk.Label(win, text='b2=', font=('Comic Sans MS', 20, 'bold'))
label_b3 = tk.Label(win, text='b3=', font=('Comic Sans MS', 20, 'bold'))

label_x0 = tk.Label(win, text='x0=', font=('Comic Sans MS', 20, 'bold'))
label_dx = tk.Label(win, text='dx=', font=('Comic Sans MS', 20, 'bold'))
label_xk = tk.Label(win, text='xk=', font=('Comic Sans MS', 20, 'bold'))

# Поля ввода
a1_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
a2_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
a3_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)

b1_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
b2_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
b3_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)

x0_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
dx_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)
xk_Entry = tk.Entry(win, font=('Comic Sans MS', 8, ), width=18)


# Кнопка расчёта данных
btn_main = tk.Button(win, text="Рассчитать",
                     font=('Comic Sans MS', 15, 'bold'),
                     command=get_table)
# Екстремумы функции
label_y_max = tk.Label(win, text=f'Ymax={y_max}', font=('Comic Sans MS', 20, 'bold'))
label_y_min = tk.Label(win, text=f'Ymin={y_min}', font=('Comic Sans MS', 20, 'bold'))
label_x_max = tk.Label(win, text=f'Xmax={x_max}', font=('Comic Sans MS', 20, 'bold'))
label_x_min = tk.Label(win, text=f'Xmin={x_min}', font=('Comic Sans MS', 20, 'bold'))

# Расположение элементов в окне
label_main.place(x=105, y=10)

label_a1.place(x=45, y=120)
label_a2.place(x=230, y=120)
label_a3.place(x=415, y=120)

label_b1.place(x=45, y=170)
label_b2.place(x=230, y=170)
label_b3.place(x=415, y=170)

label_x0.place(x=45, y=220)
label_dx.place(x=230, y=220)
label_xk.place(x=415, y=220)


a1_Entry.place(x=95, y=135)
a2_Entry.place(x=280, y=135)
a3_Entry.place(x=465, y=135)

b1_Entry.place(x=95, y=185)
b2_Entry.place(x=280, y=185)
b3_Entry.place(x=465, y=185)

x0_Entry.place(x=95, y=235)
dx_Entry.place(x=280, y=235)
xk_Entry.place(x=465, y=235)

btn_main.place(x=280, y=270)

label_y_max.place(x=0, y=650)
label_x_max.place(x=200, y=650)

label_y_min.place(x=0, y=600)
label_x_min.place(x=200, y=600)
# Отображение окна
win.mainloop()
