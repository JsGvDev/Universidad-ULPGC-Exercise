<div class="lado_izq">
	<div id="buscador" class="buscador">
		<h3>Buscador</h3>
		<form id="form_buscador" name="form_buscador" action="busqueda.php" method="post">
			<input id="busqueda" name="busqueda" type="text" value="buscar..." onfocus="if(this.value=='buscar...') this.value='';" 
			onblur="if (this.value=='') this.value='buscar...';"/><br />
			<select name="select" id="select" class="styled">
				<option value="todo" selected="selected">Todos</option>
				<option value="titulo">Películas</option>
				<option value="director">Directores</option>
				<option value="actores">Actores</option>
			</select>
			<a href="ultima_busqueda.php" id="ultimas_busquedas">Últimas busquedas</a>
			<a href="busqueda_caratula.php" id="buscador_caratulas">Buscador de carátulas</a>
			<input type="submit" name="buscar" id="buscar" value="buscar" />                    
		</form>
	</div>
	<div id="usuarios" class="usuarios">
		<h3>usuarios</h3>
	<?php if ((!isset($_SESSION['admin'])) && (!isset($_SESSION['user']))){?>	
								
		<form id="login_form" name="login_form" method="post" action="login.php">
			<input name="dni" type="text" id="usuario" value="dni" maxlength="8" onfocus="if(this.value=='dni') this.value='';" 
			onblur="if(this.value=='') this.value='dni';" />
			<input name="clave" type="password" id="clave" value="clave" maxlength="30" onfocus="if(this.value=='clave') this.value='';" 
			onblur="if(this.value=='') this.value='clave';"/>
			<div class="datos"><a href="olvide_pwd.php">Olvidé mi clave</a> | 
				<a href="http://localhost/videoclub/registro.php">Registro</a></div>
				<input type="submit" name="entrar" id="entrar" value="entrar" />
		</form>
	
	<?php } else {
			if (isset($_SESSION['admin'])) {
				echo "<div class=login><p> Bienvenid@: ".$_SESSION['admin']." (ADMIN)</p>";
				echo "<a href=".'"cerrar_sesion.php">'."<input type=submit name=salir id=salir value=salir /></a>";
				echo "</div>";
			} else {
				echo "<div class=login><p> Bienvenid@: ".$_SESSION['user']."</p>";
				echo "<a href=".'"cerrar_sesion.php">'."<input type=submit name=salir id=salir value=salir /></a>";
				echo "</div>";
			}
		  }
	?>	
	</div>
	<div id="publi" class="publi">
		<SCRIPT LANGUAGE="JavaScript"> 
			width="200"; //Anchura del banner
			height="200"; //Altura del banner
 
			banners= new Array();
			banners[0]="imagenes/publi_izq_arr/flash.swf";
			banners[1]="imagenes/publi_izq_arr/guinness.jpg";
			banners[2]="imagenes/publi_izq_arr/TED.jpg";
			banners[3]="imagenes/publi_izq_arr/YouTube.jpg";
			banners[4]="imagenes/publi_izq_arr/coca.gif";
 
			totalbanners = banners.length;
			var ahora = new Date()
			var segundos = ahora.getSeconds()
			var ad = segundos % totalbanners;
			seleccionado=banners[ad];
			localizador=seleccionado.lastIndexOf('.');
			localizador2=localizador+4
			extension=seleccionado.substring(localizador+1,localizador2); 
			archivo=seleccionado.substring(0,localizador);
 				document.write("<center>");
			if (extension=="swf"){
					flash=seleccionado;
					document.write('<OBJECT CLASSID=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" width=' + width + ' height=' + height + ' CODEBASE=\"http://active.macromedia.com/flash4/cabs/swflash.cab#version=4,0,0,0\">');
					document.write('<PARAM NAME=\"MOVIE\" VALUE=\"' + flash + '\">');
					document.write('<PARAM NAME=\"PLAY\" VALUE=\"true\">');
					document.write('<PARAM NAME=\"LOOP\" VALUE=\"true\">');
					document.write('<PARAM NAME=\"QUALITY\" VALUE=\"high\">');
					document.write('<EMBED SRC=' + flash + ' width=' + width + ' height=' + height + ' PLAY=\"true\" LOOP=\"true\" QUALITY=\"high\" PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi? P1_Prod_Version=ShockwaveFlash\">');
					document.write('</EMBED>');
					document.write('</OBJECT>');}
			else {document.write('<img src='+seleccionado+' width='+width+' height='+height+'>');
					document.write('</center>');} 
		</SCRIPT>
	</div>
	<div id="publi1" class="publi1">
		<SCRIPT LANGUAGE="JavaScript"> 
			width="240"; //Anchura del banner
			height="100"; //Altura del banner
 
			banners= new Array();
			banners[0]="imagenes/publi_izq_abj/android.jpg";
			banners[1]="imagenes/publi_izq_abj/nike.gif";
			banners[2]="imagenes/publi_izq_abj/lego.jpg";
			banners[3]="imagenes/publi_izq_abj/twitter.jpg";
			banners[4]="imagenes/publi_izq_abj/casio.gif";
 
			totalbanners = banners.length;
			var ahora = new Date()
			var segundos = ahora.getSeconds()
			var ad = segundos % totalbanners;
			seleccionado=banners[ad];
			localizador=seleccionado.lastIndexOf('.');
			localizador2=localizador+4
			extension=seleccionado.substring(localizador+1,localizador2); 
			archivo=seleccionado.substring(0,localizador);
 
			document.write("<center>");
			if (extension=="swf"){
					flash=seleccionado;
					document.write('<OBJECT CLASSID=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" width=' + width + ' height=' + height + ' CODEBASE=\"http://active.macromedia.com/flash4/cabs/swflash.cab#version=4,0,0,0\">');
					document.write('<PARAM NAME=\"MOVIE\" VALUE=\"' + flash + '\">');
					document.write('<PARAM NAME=\"PLAY\" VALUE=\"true\">');
					document.write('<PARAM NAME=\"LOOP\" VALUE=\"true\">');
					document.write('<PARAM NAME=\"QUALITY\" VALUE=\"high\">');
					document.write('<EMBED SRC=' + flash + ' width=' + width + ' height=' + height + ' PLAY=\"true\" LOOP=\"true\" QUALITY=\"high\" PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi? P1_Prod_Version=ShockwaveFlash\">');
					document.write('</EMBED>');
					document.write('</OBJECT>');}
			else {document.write('<img src='+seleccionado+' width='+width+' height='+height+'>');
					document.write('</center>');} 
		</SCRIPT>
	</div>
	<div id="reloj" class="reloj">
		<table style="float: left; margin: 0 1em 1em 0">
			<tr><td>
				<!-- element that will contain the calendar -->
				<div id="calendar-container"></div>
		
				<!-- here we will display selection information -->
				<div id="calendar-info" style="text-align: center; margin-top: 0.3em"></div>
		
			</td></tr>
		</table> 
	</div>	
</div>