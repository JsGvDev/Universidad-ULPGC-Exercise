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
    <style type="text/css">
		div.contenido form 
		{
			top: 42px;
		}		
		div.contenido form select 
		{
			position: relative;
			left: -215px;
			width: 117px;
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
		<div class="contenido">
			<h3>Añadir Película</h3>
			<form method="post" name="register" onSubmit="return validar_anadir()" action="anadir_film.php" enctype="multipart/form-data">
				<div class="form-item">
					<label>Título Película</label>
					<input id="titulo" type="text" name="titulo" maxlength="100" class="form-input">										
				</div>
				<div class="form-item">
					<label>Slug Película</label>
					<input id="slug" type="text" name="slug" maxlength="100" class="form-input">
					<div class="advert">
						<p>Título película sin espacios y caracteres anglosajones</p>
					</div>											
				</div>
				<div class="form-item">
					<label>Director</label>
					<input id="director" type="text" name="director" maxlength="50" class="form-input">											
				</div>
				<div class="form-item">
					<label>Actores</label>
					<input id="actores" type="text" name="actores" maxlength="200" class="form-input">											
				</div>
				<div class="form-item">
					<label>Titulo original</label>
					<input id="titor" type="text" name="titor" maxlength="100" class="form-input">											
				</div>
				<div class="form-item">
					<label>Género</label>	
					<select name="genero" id="genero" class="form-input">
						<?php
						if($con=mysql_connect(HOST,USER,PASS)){
							mysql_select_db(videoclub1080p,$con);
							mysql_query("SET NAMES 'utf8'");
							$consulta="(SELECT * FROM categorias)";
							if($result=mysql_query($consulta)){ 
								while(($fila=mysql_fetch_array($result))){
									echo '<option value="'.$fila['categoria'].'">'.$fila['categoria'].'</option>';
								}
							}
						}
						?>
					</select>					
				</div>
				<div class="form-item">
					<label>Formato</label>
					<select name="formato" id="formato" class="form-input">
						<?php
						if($con=mysql_connect(HOST,USER,PASS)){
							mysql_select_db(videoclub1080p,$con);
							mysql_query("SET NAMES 'utf8'");
							$consulta="(SELECT * FROM soporte)";
							if($result=mysql_query($consulta)){ 
								while(($fila=mysql_fetch_array($result))){
									echo '<option value="'.$fila['formato'].'">'.$fila['formato'].'</option>';
								}
							}
						}
						?>
					</select>											
				</div>
				<div class="form-item">
					<label>Fecha de Estreno</label>
					<input id="fecha" type="text" name="fecha" maxlength="10" value="aaaa-mm-dd" class="form-input" onfocus="if(this.value=='aaaa-mm-dd') this.value='';" onblur="if(this.value=='') this.value='aaaa-mm-dd';">
				</div>
				<div class="form-item">
					<label>Carga de carátula pequeña</label>
					<input id="imagenp" type="file"accept="image/jpeg" name="imagenp" class="form-input">
				</div>
				<div class="form-item">
					<label>Carga de carátula grande</label>
					<input id="imageng" type="file"accept="image/jpeg" name="imageng" class="form-input">
				</div>
				<div class="form-item">
					<label>Ruta del Trailer</label>
					<input id="trailer" type="text" name="trailer" maxlength="100" class="form-input" value="http://www.youtube.com/v/">
					<div class="advert">
						<p>Introduzca el código del trailer de Youtube</p>
					</div>
				</div>												

				
				<div class="buttom">
					<input name=enviar type=submit value=Añadir> <br>
				</div>				
			</form>	
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