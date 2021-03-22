package exceptions;

import nodes.ClassNode;

/**
 * Класс исключений
 * Выбрасывается при задании неверного потомка узла
 *
 * Используется в методе addChild класса ClassNode.
 * В остальных узлах нет метода для задания потомка, который
 * принимает узел общего класса - родителя Node
 *
 * @see nodes.ClassNode
 * @see nodes.IndividualNode
 *
 * @author Vladislav Sapozhnikov 19-IVT-3
 * @author Valerii Sukhorukov    19-IVT-3
 * @author Vyacheslav Mostashov  19-IVT-3
 * */
public class ChildNodeException extends Exception
{
    /**
     * Конструктор с параметром сообщением
     *
     * @param message - сообщение которое будет передано
     *                  вместе с исключением
     * */
    public ChildNodeException(String message)
    {
        super(message);
    }
}
