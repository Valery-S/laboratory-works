import React, { useState, useEffect } from 'react';
import { Link, Redirect } from 'react-router-dom';

function Add() {
    const [Name, setName] = useState(null);
    const [Likes, setLikes] = useState(0);
    const [Dislikes, setDislikes] = useState(0);
    const [Grade, setGrade] = useState(0);

    const postPicture = () => {
        const requestOptions = {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ "Name": Name, "Likes": parseInt(Likes), "Dislikes": parseInt(Dislikes), "Grade": parseInt(Grade) })
        };
        fetch("http://localhost:17499/Picture", requestOptions)
            .then(response => response.json());
    }

    return (
        <form>
            <p>Введите имя файла, который нужно добавить</p>
            <div className="form-group">
                <label htmlFor="Name" className="col-md-2 control-label">Название:</label>
                <div className="col-md-4">
                    <input type="text" name="Name" className="form-control" onChange={(e) => setName(e.target.value)} />
                </div>
            </div>
            <div className="form-group">
                <div className="col-md-offset-2 col-md-10">
                    <Link type="submit" onClick={postPicture} className="btn btn-default" to={{ pathname: '/' }}>Добавить</Link>
                </div>
            </div>
        </form>
        
    );
}

export { Add };