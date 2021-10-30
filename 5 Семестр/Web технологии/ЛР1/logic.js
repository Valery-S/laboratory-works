function color_selection() {
    var color = document.getElementById("list").value;

    switch (color) {
        case "RE":
            document.querySelector('.sq').style.backgroundColor = "red";
            break;
        case "OR":
            document.querySelector('.sq').style.backgroundColor = "orange";
            break;
        case "YE":
            document.querySelector('.sq').style.backgroundColor = "yellow";
            break;
        case "GR":
            document.querySelector('.sq').style.backgroundColor = "green";
            break;
        case "BL":
            document.querySelector('.sq').style.backgroundColor = "blue";
            break;
        case "PU":
            document.querySelector('.sq').style.backgroundColor = "purple";
            break; 
        default:
            break;
    }
}

function colors(color) {
    document.querySelector('.sq').style.backgroundColor = color;
}