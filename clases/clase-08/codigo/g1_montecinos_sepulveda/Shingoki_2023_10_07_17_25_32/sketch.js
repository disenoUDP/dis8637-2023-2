// Copyright (c) 2019 ml5
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/* ===
ml5 Example
PoseNet example using p5.js
código del semáforo basado en "Traffic Light" por esthers7012
=== */

let video;
let poseNet;
let poses = [];
let contadorPersonas = 0;

function setup() {
  createCanvas(400, 400);
  frameRate(0.1);
  video = createCapture(VIDEO);
  video.size(width, height);

  // detección individual en posenet
  poseNet = ml5.poseNet(video, modelReady);
  
  // esto setea la variable local "poses"
  poseNet.on('pose', function(results) {
    poses = results;
  });
  
  // esconde el video y muestra solo el canvas
  video.hide();
  
}

function draw() {
  
  // colores del canvas
  background(220);
 
  // valor de la línea del rectángulo
  strokeWeight(6);
  
  // color del rectángulo
  fill(255);
  
  // crea el rectángulo y ponlo en esta coordenada
  rect(135, 25, 130, 350, 30);
  
  // crea la primera elipse y ponla en esta coordenada, color rojo
  ellipse(200, 305, 80, 80); // ellipse 1
  
  // crea la segunda elipse y ponla en esta coordenada, color amarillo
  ellipse(200, 200, 80, 80); // ellipse 2
  
  // crea la tercera elipse y ponla en esta coordenada, color verde
  ellipse(200, 95, 80, 80); // ellipse 3
  
  contadorPersonas = poses.length;
  
  // imprime en la consola "personas detectadas" y su valor
  console.log("Personas detectadas:", contadorPersonas);
  
  // si el número de personas es mayor o igual a cero o menor o igual a 5, enciende la luz verde
  if(contadorPersonas >= 0 && contadorPersonas <= 5) {
    console.log("Fila corta (Luz verde)");
    fill(0, 255, 0);
    ellipse(200, 305, 80, 80);
    
    // si el número de personas es mayor o igual a seis o menor o igual a diez, enciende la luz amarilla
  } else if(contadorPersonas >= 6 && contadorPersonas <= 10) {
    console.log("Fila media (Luz amarilla)");
    fill(255, 255, 0);
    ellipse(200, 200, 80, 80);
    
    // si el número de personas es mayor o igual a once o menor o igual a veinte, enciende la luz roja
  } else if (contadorPersonas >= 11 && contadorPersonas <= 20) {
    console.log("Fila larga (Luz roja)");
    fill(230, 3, 3);
    ellipse(200, 95, 80, 80);

  }
}

function modelReady() {
  select('#status').html('Model Loaded');
}
