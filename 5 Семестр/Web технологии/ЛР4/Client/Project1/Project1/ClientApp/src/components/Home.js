import React, { useState, useEffect } from 'react';
import { Link, Redirect } from 'react-router-dom';

function Home() {
    const [pictures, setPicture] = useState([]);

    useEffect(() => {
        fetch("http://localhost:17499/Picture")
            .then((response) => response.json())
            .then((result) => setPicture(result))
    }, []);


    const DeletePicture = (e) => {
        const id = e.target.elements.id.value;
        const requestOptions = {
            method: 'DELETE',
            headers: { 'Content-Type': 'application/json' },
        };
        fetch(`http://localhost:17499/Picture/${id}`, requestOptions);
    }

    return (
        <div>
            <h3>Рейтинг картинок</h3>
            <table className="table table-bordered">
                <thead>
                    <tr className="table-dark">
                        <td>Имя файла</td>
                        <td>Количество лайков</td>
                        <td>Количество дизлайков</td>
                        <td>Оценка картинки</td>
                        <td></td>
                        <td></td>
                    </tr>
                </thead>
                {pictures.map(picture => (
                    <tbody>
                        <tr>
                            <td>{picture.name}</td>
                            <td>{picture.likes}</td>
                            <td>{picture.dislikes}</td>
                            <td>{picture.grade}</td>
                            <td><Link className="btn btn-default" to={{ pathname: '/Update', data: picture }}>Оценить</Link></td>
                            <td><form onSubmit={DeletePicture}>
                                <input type="hidden" value={picture.id} name="id" />
                                <button className="btn btn-default">Удалить</button>
                            </form>
                            </td>
                        </tr>
                    </tbody>
                ))}
            </table>
            <Link className="btn btn-default" to={{ pathname: '/Add' }}>Добавить</Link>
        </div>   
   );

}
export { Home };
