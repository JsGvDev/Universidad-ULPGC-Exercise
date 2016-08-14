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
	<div class="peliytrailer">
			<?php
			if($con=mysql_connect(HOST,USER,PASS)){
				mysql_select_db(videoclub1080p,$con);
				mysql_query("SET NAMES 'utf8'");
				$consulta="(SELECT * FROM peliculas WHERE slugpeliculas='" . $_GET['slugpeliculas'] . "')";
					if($result=mysql_query($consulta)){ 
						$fila=mysql_fetch_array($result);					
							echo "<h4>&nbsp; $fila[genero]: &nbsp;&nbsp; $fila[titulo]</h4>";
							echo "<div class=caratulagrande>";
							echo '<img src="imagenes/caratulas/g'.$fila[slugpeliculas].'.jpg" width=282 height=417>';
							echo "</div> ";
							echo '<h5>&nbsp; Trailer: </h5>';
							echo "<div class=trailer>";
							echo '&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;<object type="application/x-shockwave-flash" style="width:425px;height:320px" data="'.$fila[trailer].'"><param name="movie" value="'.$fila[trailer].'" /></object>';
							echo "</div> ";
							echo '<div class=datospeli>';
							echo '<div class=infopeli>';
							echo "<h5> Director: </h5>";
							echo "<p>$fila[director]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';	
							echo "<h5> Actores: </h5>";
							echo "<p>$fila[actores]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';
							echo "<h5> Titulo original: </h5>";
							echo "<p>$fila[titulooriginal]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';
							echo "<h5> Genero: </h5>";
							echo "<p>$fila[genero]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';
							echo "<h5> Fecha de estreno: </h5>";
							echo "<p>$fila[fechaestreno]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';
							echo "<h5> Alquiler: </h5>";
							echo "<p>$fila[alquilerdiario]</p>";
							echo "</div> ";
							echo '<div class=infopeli>';
							echo "<h5> Formato: </h5>";
							echo "<p>$fila[formato]</p>";
							echo "</div> ";
							echo "</div> ";									
					}else{
						echo 'Base de datos vacía';
					}
				}else{
					echo 'Error en la conexión';
				}
			?>	
	</div>
	 
</div>
<?php
	include("carrusel.php");	
	include("banners.php");
?>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>