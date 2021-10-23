const Joi = require('joi');
const express = require('express');
const app = express();


app.use(express.json());
//making http request using express

// (req, res) =>{
//     res.send('HElo World!');
// });  Route Handler.

const courses = [
    {id: 1, name: 'course1'},
    {id: 2, name: 'course2'},
    {id: 3, name: 'course3'}
];

app.get('/', (req, res) =>{
    res.send('Hello World!');
});

app.get('/api/courses', (req,res) => {
    res.send(courses);
});
//how to respond to post method

// ye chij me aa rha h error
app.post('/api/courses', (req, res) => {
    //schema define the shape of the object,property of object etc.
    const schema = {
        name: Joi.string().min(3).required()
    };

    const result = Joi.validate(req.body, schema);
    console.log(result);

    if(!req.body.name || req.body.name.length < 3)
    {
        // 400 Bad Request
        res.status(400).send('Name id required and should be minimum 3 character long');
        return;
    }

    const course = {
        id: courses.length + 1,
        name: req.body.name
    };
    courses.push(course);
    res.send(course);
});

// to get the singal course
app.get('/api/courses/:id', (req, res) => {
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if(!course) res.status(404).send('The course was not found with the given ID');
    res.send(course); 
});

// PORT is used to process object
const port = process.env.PORT || 3000;
app.listen(port, ()=> console.log(`Listening on port ${port}...`));