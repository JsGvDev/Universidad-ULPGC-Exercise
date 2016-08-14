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
	<div class="admini">
	<h3>Opciones de administrador</h3>
	<a href="activar.php">
		<div class="buttom1"><input name=activar type=submit value='Activar usuario'> <br>
	</div></a>
	<a href="permiso.php">
		<div class="buttom2"><input name=permiso type=submit value='Dar permiso admin'> <br>
	</div></a>
	<a href="anadir.php">
		<div class="buttom3"><input name=anadir type=submit value='Añadir película'> <br>
	</div></a>
	</div>				
	</div>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>