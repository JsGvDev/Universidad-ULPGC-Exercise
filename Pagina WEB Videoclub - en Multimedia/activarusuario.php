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
	
		if($con=mysql_connect(HOST,USER,PASS)){
			mysql_select_db(videoclub1080p,$con);
			mysql_query("SET NAMES 'utf8'");
			$dni = $_GET[dni];
			mysql_query("update usuarios set activo = '1' WHERE dni ='".$dni."'");
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
	?>
		<div class="contenido">
			<h3>Actualización realizada</h3>
			<p>El usuario ha sido activado.</p>				
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