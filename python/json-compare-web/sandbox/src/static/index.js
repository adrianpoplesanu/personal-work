let data = {
    id: 123,
    name: "aaa"
}

function compare() {
    let post = JSON.stringify(data)
    const url = "/compare"
    let xhr = new XMLHttpRequest()
    xhr.open('POST', url, true)
    xhr.setRequestHeader('Content-type', 'application/json; charset=UTF-8')
    xhr.send(post);
    xhr.onload = function () {
        console.log(JSON.parse(xhr.response)); 
        //if(xhr.status === 201) {
        //    console.log("Post successfully created!") 
        //}
    }
}

/*function compare() {
    //console.log("bbb");
    fetch("/compare", {
        method: 'post',
        body: data,
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        }
    }).then((response) => {
        console.log("aaa");
        console.log(response.json())
        return response.json()
    //}).then((res) => {
    //    console.log("bbb");
    //    if (res.status === 201) {
    //        console.log("Post successfully created!")
    //    }
    }).catch((error) => {
        console.log("ccc");
        console.log(error)
    })
}*/
