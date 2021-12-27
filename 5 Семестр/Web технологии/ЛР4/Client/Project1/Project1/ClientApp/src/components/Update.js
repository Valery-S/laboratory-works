import React, { useState, useEffect } from 'react';
import { Link, Redirect } from 'react-router-dom';

function Update(props) {
    const [id, setId] = useState(0);
    const [name, setName] = useState(null);
    const [likes, setLikes] = useState(0);
    const [dislikes, setDislikes] = useState(0);
    const [grade, setGrade] = useState(0);
    const { data } = props.location;

    useEffect(() => {
        setId(data.id)
        setName(data.name)
        setLikes(data.likes)
        setDislikes(data.dislikes)
        setGrade(data.grade)
    }, []);

    const PutPicture = () => {
        const requestOptions = {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ "Id": id, "Name": name, "Likes": parseInt(likes), "Dislikes": parseInt(dislikes), "Grade": parseInt(grade )})
        };
        fetch(`http://localhost:17499/Picture`, requestOptions)
            .then(response => response.json());
    }

    return (
        <form>
            <p>Для оценки увеличть занчение на 1 в одном из полей: "Лайки" или "Дизлайки".</p>
            <p> Увеличьте или уменьшите значение поля "Оценка" на 1 в соответствии с вашим выбором.</p>
            <div className="form-group">
                <label htmlFor="Description" className="col-md-2 control-label">Лайки:</label>
                <div className="col-md-4">
                    <input type="text" name="Likes" className="form-control" value={likes} onChange={(e) => setLikes(e.target.value)} />
                </div>
            </div>
            <div className="form-group">
                <label className="col-md-2 control-label">Дизлайки:</label>
                <div className="col-md-4">
                    <input type="text" name="Dislikes" className="form-control" value={dislikes} onChange={(e) => setDislikes(e.target.value)} />
                </div>
            </div>
            <div className="form-group">
                <label className="col-md-2 control-label">Оценка:</label>
                <div className="col-md-4">
                    <input type="text" name="Dislikes" className="form-control" value={grade} onChange={(e) => setGrade(e.target.value)} />
                </div>
            </div>
            <div className="form-group">
                <div className="col-md-offset-2 col-md-10">
                    <Link type="submit" onClick={PutPicture} className="btn btn-default" to={{ pathname: '/' }}>Оценить</Link>
                </div>
            </div>
        </form>
   );
}

export { Update };