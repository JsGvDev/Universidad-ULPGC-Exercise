<?php
	session_start();
	$_SESSION['usuario']=1;
	include('macro.php');
?>

<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<link rel="stylesheet" type="text/css" href="listados.css" />
	<link rel="stylesheet" type="text/css" href="calendario_css.css" />
	<link rel="stylesheet" type="text/css" href="jquery_css.css" />
	<link rel="stylesheet" type="text/css" href="jquery_css_novedad.css" />
	<script type="text/javascript" language="javascript" src="jquery/jquery.js"></script>
	<script type="text/javascript" language="javascript" src="jquery/jquery.carouFredSel-5.5.5-packed.js"></script>
	<link rel="stylesheet" type="text/css" href="JSCal2/css/jscal2.css" />
    <link rel="stylesheet" type="text/css" href="JSCal2/css/border-radius.css" />
    <link rel="stylesheet" type="text/css" href="JSCal2/css/gold/gold.css" />
	<link rel="stylesheet" type="text/css" href="reloj.css" />
    <script type="text/javascript" src="JSCal2/js/jscal2.js"></script>
    <script type="text/javascript" src="JSCal2/js/lang/es.js"></script>
<title>Videoclub 1080p</title>
</head>
<body>
<div class="principal">
<?php
	include("header.php");
?>
	<div class="cuerpo">
	<?php
		include("lado_izq.php");
		include("estrenos.php");
	?>
	
	<?php
		if($con=mysql_connect(HOST,USER,PASS)){
			mysql_select_db(videoclub1080p,$con);
			mysql_query("SET NAMES 'utf8'");

	echo "<div class=list_novedad>";
		
		echo "<ul>";
			
			$NumPelis=0;
			//$npaginas=6;
			$consulta="(SELECT * FROM peliculas WHERE 1 )";
			if($result=mysql_query($consulta)){ 
				while(($fila=mysql_fetch_array($result))){
					switch ($_SESSION['ult_bus_sel']) {
						case "todo": $pos1 = stripos($fila[titulo], $_SESSION['ult_bus_pal']);
									 $pos2 = stripos($fila[director], $_SESSION['ult_bus_pal']);
									 $pos3 = stripos($fila[actores], $_SESSION['ult_bus_pal']);
							break;
						case "titulo": $pos = stripos($fila[titulo], $_SESSION['ult_bus_pal']);//devuelve posicion si encuentra, falso si no encuentra
							break;
						case "director": $pos = stripos($fila[director], $_SESSION['ult_bus_pal']);
							break;
						case "actores": $pos = stripos($fila[actores], $_SESSION['ult_bus_pal']);
							break;
					}
					if ($_SESSION['ult_bus_sel']==todo) {
						if (($pos1 !== false) || ($pos2 !== false) || ($pos3 !== false)) {
						echo "<li>";
							echo "<h4>&nbsp; $fila[titulo]: &nbsp;&nbsp; $fila[fechaestreno]</h4>";
							echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
							echo "<h5>&nbsp; Director: </h5>";
							echo "<p>$fila[director]</p>";
							echo "<h5>&nbsp; Actores: </h5>";
							echo "<p>$fila[actores]</p>";
							$NumPelis++;
						echo "</li>";
						}	
					} else {
						if ($pos !== false) {
						echo "<li>";
							echo "<h4>&nbsp; $fila[titulo]: &nbsp;&nbsp; $fila[fechaestreno]</h4>";
							echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
							echo "<h5>&nbsp; Director: </h5>";
							echo "<p>$fila[director]</p>";
							echo "<h5>&nbsp; Actores: </h5>";
							echo "<p>$fila[actores]</p>";
							$NumPelis++;
						echo "</li>";
						}	
					}
				}				
			}else{
				echo 'Base de datos vacía';
			}
			echo "<li>";
				if ($NumPelis > 0) {					
						echo "<p style=\"font-size: 19px\" align=center> $NumPelis peliculas encontradas </p>";
				} else {
						echo "<p> Ningún resultado encontrado </p>";
				}
			echo "</li>";
		echo"</ul>";
	echo"</div>";
		}else{
			echo 'Error en la conexión';
		}
	?>
	</div>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>