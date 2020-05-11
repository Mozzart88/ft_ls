function download(t)
{
	let bb;
	if (t == "html")
		bb = new Blob( [document.querySelector("html").innerHTML], {type: 'text/html'});
	if (t == "txt")
		bb = new Blob( [document.body.innerText], {type: 'text/plain'});
	let a = document.createElement('a');
	let name = location.pathname.split('/');
	name = name[name.length - 1];
	name = name.split('.')[0];

	a.href = window.URL.createObjectURL(bb);
	a.textContent = "download body";
	a.download = name + "_RUG." + t;
	// document.body.appendChild(a);
	a.click();
}
function download_html()
{
	download("html");
}
function download_txt()
{
	download("txt");
}
window.onload = () => {
	let b1 = document.createElement("button");
	let b2 = document.createElement("button");
	b1.onclick = download_html;
	b1.textContent = "Download html";
	document.body.insertBefore(b1, document.body.firstElementChild);
	b2.onclick = download_txt;
	b2.textContent = "Download text";
	document.body.insertBefore(b2, document.body.firstElementChild);
}