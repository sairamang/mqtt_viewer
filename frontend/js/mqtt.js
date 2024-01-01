let myVar;
let g_ipaddress;
function start() {
  console.log("start");
  myVar=setInterval(httpget, 500);
}
function stop() {
  console.log("stop");
  clearInterval(myVar);
}
function connect()
{
  let ipaddress=document.getElementById("ipaddressid");
  let ipaddr_str=ipaddress.value;
  if(!ipaddr_str)
  {
    ipaddr_str="127.0.0.1:8080";
    console.log("undefined");
  }
  let ipaddress_final="http://"+ipaddr_str+"/connect";
  console.log(ipaddress_final);
  const xhr = new XMLHttpRequest();
  xhr.open("GET", ipaddress_final);
  xhr.send();
    xhr.responseType = "text";
    xhr.onload = () => {
      if (xhr.readyState == 4 && xhr.status == 200) {
        //console.log(xhr.response);
        let data=xhr.response;
        if(data=="success")
        {
          console.log("Connection success");
          const con_btn = document.querySelector(".connect_btn");
          con_btn.innerText='Connected to '+ipaddr_str;  
          g_ipaddress=ipaddr_str;      
        }
      } else {
        const con_btn = document.querySelector(".connect_btn");
        con_btn.innerText='Connection Failed '+ipaddr_str;  
        console.log(`Error: ${xhr.status}`);
    }
  };
}
  

async function fetchAsync() {
  // await response of fetch call
  let ipaddress_final="http://"+ipaddress+"/mqtt";
  let response = await fetch(ipaddress_final, {
    mode: 'no-cors',
    method: "GET",
    cache: "no-cache",
    credentials: "omit",
    headers: {
      "Accept": "*/*",
      "Accept-Encoding": "gzip, deflate, br",
      "connection": "keep-alive",
      "Content-Type": "text/plain"
    }
  });
  // only proceed once promise is resolved
  let data = await response;
  // only proceed once second promise is resolved
  if (data.json.length != 0) {
    console.log(JSON.stringify(data.json()));
  }
  console.log(data)
  return data;
}
let viewmode="onebyone";
let toggle_trigger=false;
function clearall()
{
  if(viewmode=="onebyone")
  {
    viewmode="parallel";
  }
  else 
  {
    viewmode="onebyone";
  }
  toggle_trigger=true;
  const table = document.getElementById('id_tbody');
  childnodes=table.childNodes;
  for(let i=childnodes.length-1;i>=0;i--)
  {
    table.removeChild(childnodes[i]);
  }
}

function httpget() {
  let ipaddress_final="http://"+g_ipaddress+"/mqtt";
  const xhr = new XMLHttpRequest();
  xhr.open("GET", ipaddress_final);
  xhr.send();
  xhr.responseType = "json";
  xhr.onload = () => {
    if (xhr.readyState == 4 && xhr.status == 200) {
      //console.log(xhr.response);
      let data=xhr.response;
      console.log(JSON.stringify(data));
      const obj = data;
      let no_of_elements=obj["no"];
      for(let i=0;i<no_of_elements;i++)
      {
        let data_packet=obj["data"][i];
        console.log(JSON.stringify(data_packet));
        addrow(data_packet["id"],data_packet["Topicname"],data_packet["Payload"]);
      }
    } else {
      console.log(`Error: ${xhr.status}`);
    }
  };
}


let numItems = 0;
function addrow(sno,topicname,payload) {
  const table = document.getElementById('id_tbody');
  numItems++;
  var row = table.insertRow(0);
  var cell1 = row.insertCell(0);
  var cell2 = row.insertCell(1);
  var cell3 = row.insertCell(2);
  cell1.innerHTML=sno;
  cell2.innerHTML=topicname;
  cell3.innerHTML=payload;
  // You could also do the same for the cells and inputs
};


