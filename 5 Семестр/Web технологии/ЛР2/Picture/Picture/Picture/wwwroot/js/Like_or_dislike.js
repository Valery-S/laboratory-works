function next_foto() {
	var rotator = document.getElementById('rotator'),
		dir = '../Image/50 Foto/',
		src = rotator.src;

	var num = 0,
		num_f = Number(src[src.length - 5]),
		num_s = Number(src[src.length - 6]),
		len = 50;

	if (isNaN(num_s)) { num = num_f }
	else { num = num_s * 10 + num_f; }


	num++;
	if (num > len) { num = 1; }
	rotator.src = dir + num + '.jpg';

}
