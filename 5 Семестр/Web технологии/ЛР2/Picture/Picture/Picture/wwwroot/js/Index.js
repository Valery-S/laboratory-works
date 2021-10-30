window.onload = function () {
	var d = document.createElement("d");
	d.className = "foto";
	document.body.append(d);

	var dir = '../Image/50 Foto/';
	var i = 1;
	for (i; i <= 50; i++) {
		var img = document.createElement("img");
		img.class = 'img' + i;
		img.width = '480';
		img.height = '270';
		img.id = "img" + i;
		img.src = dir + i + '.jpg';
		d.appendChild(img);
	}

	var top = 50;
	for (i = 1; i <= 50; i++) {
		var im = document.getElementById('img' + i);
		
		if (i > 2 && i%2==1) {
			top =top+100;
		}

		im.style.position = 'relative';
		im.style.top = top+'px';
		if (i % 2 == 0) {im.style.left = "270px"; }
		if (i % 2 == 1) {im.style.left = "10px"; }
    }
}

