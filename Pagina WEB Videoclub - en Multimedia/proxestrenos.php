
<?php
	if($con=mysql_connect(HOST,USER,PASS)){
			mysql_select_db(videoclub1080p,$con);
			mysql_query("SET NAMES 'utf8'");
	
	echo"<div class=contenido>";
			$val=1;
			echo "<h4 class=proxestr>PRÓXIMOS ESTRENOS</h4>";
			$consulta='SELECT * FROM peliculas WHERE fechaestreno="0000-00-00"';
			//echo $consulta;
			if($result=mysql_query($consulta)){ 
				while(($fila=mysql_fetch_array($result))){
					switch($val){
						case 1: echo "<div class=cont_izq_arr>";
							break;
						case 2: echo "<div class=cont_dch_arr>";
							break;
						case 3: echo "<div class=cont_izq_abj>";
							break;
						case 4: echo "<div class=cont_dch_abj>";
							break;
					}
						echo "<h4>&nbsp; $fila[genero]: &nbsp;&nbsp; $fila[titulo]</h4>";
						echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
						echo "<h5>&nbsp; Director: </h5>";
						echo "<p>&nbsp; $fila[director]</p>";
						echo "<h5>&nbsp; Actores: </h5>";
						echo "<p>$fila[actores]</p>";
					echo "</div> ";
					$val++;
				}				
			}else{
				echo 'Base de datos vacía';
			}
	echo "</div>";
	}else{
		echo 'Error en la conexión';
	}

?>