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
	<style type="text/css">
		.contenido img, .list_novedad img 
		{
			left: 105px;
		}		
	</style>
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
			
			//$NumPelis=0;
			//$npaginas=6;
			$consulta="(SELECT * FROM peliculas WHERE 1 )";
			if($result=mysql_query($consulta)){ 
				while(($fila=mysql_fetch_array($result))){
					
						echo "<li>";
							echo "<h4>&nbsp; $fila[titulo]: &nbsp;&nbsp;</h4>";
							echo '<a href="imagenes/caratulas/g'.$fila[slugpeliculas].'.jpg"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
						echo "</li>";
				}				
			}else{
				echo 'Base de datos vacía';
			}			
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