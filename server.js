const express = require('express')
const app = express()
const options = {
    setHeaders:(res,path,stat)=>{
        if(path.endsWith('.wasm')){
            res.set('Content-Type', 'application/wasm')
        }
    }
}
app.use(express.static('public', options)) // options to set content-type wasm not required for newer version of express

app.listen(2222, ()=> console.log("server running on port 2222"))
