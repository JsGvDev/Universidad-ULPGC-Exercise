<?php
	
	session_start();
	$_SESSION['usuario']=1;
	
	if (isset($_SESSION['user'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	if (isset($_SESSION['admin'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	include('macro.php');
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
		if ($_GET['f']==fallo){
	?>
		<div class="contenido">
			<h3>Login Fallido</h3>
			<p>Usuario pendiente de ser activado. Por favor, vuelva a intentarlo mas tarde.</p>
			<a href="index.php">
				<div class="buttom"><input name=registrar type=submit value='Volver'> <br>
				</div></a>				
		</div>
		<?php } else { ?>
		<div class="contenido">
			<h3>Login Fallido</h3>
			<p>Los datos introducidos no son correctos. El usuario o el password son incorrectos. Por favor, vuelva a intentarlo.</p>
			<a href="index.php">
				<div class="buttom"><input name=registrar type=submit value='Volver'> <br>
				</div></a>				
		</div>
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