<?php
	
	session_start();
	
	if (isset($_SESSION['user'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	if (!isset($_SESSION['admin'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	include('macro.php');
	
	$titulo = $_POST["titulo"];
	$slug = $_POST["slug"];
	$director = $_POST["director"];
	$actores = $_POST["actores"];
	$titor = $_POST["titor"];
	$genero = $_POST["genero"];
	$formato = $_POST["formato"];
	$fecha = $_POST["fecha"];
	$imagenp = $_FILES["imagenp"]['name'];
	//$imageng = $_FILES["imageng"]['name'];
	$trailer = $_POST["trailer"];
	
	//ruta para la imagen
	$directorio = $_SERVER['DOCUMENT_ROOT'].'/Videoclub/imagenes/caratulas/';
	
	//movemos las imagenes al servidor
	move_uploaded_file($_FILES['imagenp']['tmp_name'],$directorio.$imagenp);
	move_uploaded_file($_FILES['imageng']['tmp_name'],$directorio.'g'.$slug.'.jpg');
		
	if($con=mysql_connect(HOST,USER,PASS)){
		mysql_select_db(videoclub1080p,$con);
		mysql_query("SET NAMES 'utf8'");
		$resp=0;	
		$consulta=("SELECT titulo FROM peliculas WHERE titulo='".$_POST["titulo"]."'");
		if($result=mysql_query($consulta)){
			if(mysql_num_rows($result) > 0){
				$resp=1;						
			} else {
				mysql_query("insert into peliculas (imagenpeli,titulo,director,actores,titulooriginal,genero,fechaestreno,alquilerdiario,formato,slugpeliculas,trailer) values ('imagenes/caratulas/$imagenp','$titulo','$director','$actores','$titor','$genero','$fecha','2,50€','$formato','$slug','$trailer')",$con);			
			}
		}			
	} else {
		echo 'Error en la conexión';
	}
			
	mysql_close($con);
?>
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<link rel="stylesheet" type="text/css" href="mystile.css" />
	<link rel="stylesheet" type="text/css" href="registro_css.css">
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
	if ($resp==0) {
	?>
		<div class="contenido">
			<h3>Película añadida</h3>
			<p>Se ha añadido la película correctamente.</p>
		</div>
	<?php } else { ?>
		<div class="contenido">
			<h3>Fallo al añadir</h3>
			<p>La película ya existe. Por favor, vuelva a intentarlo.</p>
		</div>
		<a href="anadir.php">
			<div class="buttom"><input name=registrar type=submit value='Volver'> <br>
			</div>
		</a>
	<?php } ?>
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