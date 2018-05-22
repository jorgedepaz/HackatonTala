# HackatonTala
Un repositorio en desarollo que contiene el actual progreso de un proyecto hecho para detectar el sonido de una motosierra a travez de un sensor que consta de una barilla de cobre o aluminio, un microfono y filtros activos. La idea es incrustar la barilla en la tierra a 60cm de la superficie para captar los sonidos provenientes de las raíces de los árboles, la frecuencia del sonido buscada oscila entre los 130hz y 300hz.

Una alarma se dispara en el momento que se detecta este sonido, pero antes pasa por un filtrado digital en arduino para evitar falsas alarmas, este se basa en la constancia del sonido.

La alarma se envia a travez de la red por medio de un esp8266 con el protocolo mqtt, este protocolo esta pensado para redes con un bajo consumo de ancho de banda, que lo hace ideal para aplicaiones iot, las alertas son recividas por el broker en el servidor y deplegadas en la interfaz grafica de home assistant.

Los filtros activos se diseñaron con los amplificadores operacionales lm324 y 741.

Imagen:<a href="https://drive.google.com/file/d/1AOsEYE8CTa3KblfU12V1wqZuaomCWLHy/view?usp=sharing"><img src="https://drive.google.com/file/d/1AOsEYE8CTa3KblfU12V1wqZuaomCWLHy/view?usp=sharing" /></a>

Libreria utilizada en el ESP8266: https://github.com/knolleary/pubsubclient
