let c = document.getElementById("container");


let i = document.createElement("input");
i.value = "ABC"
i.setAttribute("style", "width: 150px")
let b = document.createElement("button");
b.textContent = "ADD JODWORK";
b.setAttribute("style", "width: 158px");
c.appendChild(i);
c.appendChild(b);
let t = document.createElement("ul");
c.appendChild(t);

let arrCV = [];
function CongViec (tencv) {
     let today = new Date();
     let date = today.getDate() + '-' + (today.getMonth()+1) + '-' + today.getFullYear();
     let time = today.getHours() + ":" + (today.getMinutes()) + ":" + today.getSeconds();

     return {
          tencv: tencv,
          date: date,
          time: time,
     }
}
b.onclick = function () {
     arrCV.push(CongViec(i.value));
     let li = document.createElement("li");
     t.appendChild(li);
     let namevc = document.createElement("p");
     let ngay = document.createElement("p");
     let gio = document.createElement("p");
     namevc.textContent = arrCV[arrCV.length-1].tencv;
     ngay.textContent = arrCV[arrCV.length-1].date;
     gio.textContent = arrCV[arrCV.length-1].time;
     li.appendChild(namevc);
     li.appendChild(ngay);
     li.appendChild(gio);
}