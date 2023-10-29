const {spawnSync} = require('child_process');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 80;

const path = 'lib/c/main.exe';
//const path = 'lib/c/main';

app.use(bodyParser.urlencoded({extended: false}));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/pages/index.html');
})

app.all('/encode', (req, res) => {
    let s = req.body.s ?? req.query.s ?? '';
    let base64 = Buffer.from(s).toString('base64');
    let string = gene_code('encode', base64)
    res.send(string);
});
app.all('/decode', (req, res) => {
    let s = req.body.s ?? req.query.s ?? '';
    let base64 = gene_code('decode', s);
    let string = Buffer.from(base64, 'base64').toString('utf-8');
    res.send(string);
});
app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});

function gene_code(type, string) {
    const proc = spawnSync(path, [type], {
        input: string + '\n', // 将数据写入子进程的标准输入
        stdio: 'pipe', // 指定标准输入/输出流
        encoding: 'utf-8', // 编码方式
    });
    return proc.stdout;
}
