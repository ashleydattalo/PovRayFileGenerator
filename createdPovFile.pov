camera {
  location <0, 0, -15>  
  up <0, 1, 0>  
  right <1.333, 0, 0>  
  look_at <0, 0, 0>  
}

light_source {<10, 10, -10> color rgb <3.5, 3.5, 3.5>}

light_source {<-10, 10, -10> color rgb <1.5, 1.5, 1.5>}

plane { <0, 1, 0>, -12
  pigment { color rgb <0.9, 0.8, 0.9> }
  finish {
     ambient 0.3 diffuse 0.5 specular 0 roughness 0 ior 0 reflection 0.6 refraction 0
  }
  translate <0, 0, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <-15, -15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <-15, 0, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <-15, 15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <0, -15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <0, 0, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <0, 15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <15, -15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <15, 0, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}

box { <-5, -5, 20>, <5, 5, 30>
  pigment { color rgb <1, 1, 1> }
  finish {
     ambient 0.2 diffuse 0.4 specular 0 roughness 0 ior 0 reflection 0.8 refraction 0
  }
  translate <15, 15, 0>
  scale <1, 1, 1>
  rotate <0, 0, 0>
}
