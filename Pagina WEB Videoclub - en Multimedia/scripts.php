	<script type="text/javascript" language="javascript">
		$(function() {
			$("#foo2").carouFredSel({
				circular: true,
				infinite: false,
				align	: "center",
				items: {visible: 4},
				auto 	: {
					pauseDuration: 2500,
					duration: 2500
				},
				scroll	: {
					items	: "page",
					duration: 2500,
					pauseOnHover: true
				},
				prev	: {	
					button	: "#foo2_prev",
					key		: "left"
				},
				next	: { 
					button	: "#foo2_next",
					key		: "right"
				},
				pagination	: "#foo2_pag"
			});
			$("#nov").carouFredSel({
				items 		: 1,
				direction	: "up",
				auto : {
					easing		: "elastic",
					duration	: 1000,
					pauseDuration: 2000,
					pauseOnHover: true
				}
			}).find(".slide").hover(
				function() { $(this).find("div").slideDown(); },
				function() { $(this).find("div").slideUp();	}
			);
		});
		//Calendario reloj
		var DATE_INFO = {
			20120617: { klass: "highlight", tooltip: "Fin oferta 2x1" },
			20120630: { klass: "highlight", tooltip: "Ultimo dia reserva Los Vengadores" }
		};
		function getDateInfo(date, wantsClassName) {
			var as_number = Calendar.dateToInt(date);
			if (String(as_number).indexOf("0628") == 4) {
				// my birthday :-p
				return { klass: "estreno", tooltip: "ESTRENO: El caballero oscuro: la leyenda renace" };
			}
			if (as_number >= 20120618 && as_number <= 20120624)
			return {
				klass   : "highlight2",
				tooltip : "<div style='text-align: center'>%Y/%m/%d (%A)" +
						"<br />Semana fantastica, todo a mitad de precio!</div>" // formatted by printDate
			};
			return DATE_INFO[as_number];
		};
		Calendar.setup({
			cont          : "calendar-container",
			fdow     	  : 1,
			dateInfo 	  : getDateInfo, // pass our getDateInfo function
			weekNumbers   : true,
			selectionType : Calendar.SEL_MULTIPLE,
			selection     : Calendar.dateToInt(new Date()),
			showTime      : 12,
			onSelect      : function() {
								var count = this.selection.countDays();
								if (count == 1) {
									var date = this.selection.get()[0];
									date = Calendar.intToDate(date);
									date = Calendar.printDate(date, "%A, %B %d, %Y");
									$("calendar-info").innerHTML = date;
								} else {
									$("calendar-info").innerHTML = Calendar.formatString(
										"${count:no date|one date|two dates|# dates} selected",
										{ count: count }
									);
								}
							},
			onTimeChange  : function(cal) {
								var h = cal.getHours(), m = cal.getMinutes();
								// zero-pad them
								if (h < 10) h = "0" + h;
								if (m < 10) m = "0" + m;
								$("calendar-info").innerHTML = Calendar.formatString("Time changed to ${hh}:${mm}", {
									hh: h,
									mm: m
								});
							}
		});
		function validar(){
		if (document.register.nombre.value=="") {
			alert("Debe indicar su Nombre")
			return false
		} else {
			var letyEspa =/[A-Za-zñÑ\s]/;		
			var name=document.register.nombre.value;
			if (letyEspa.test(name) == false) {
				alert('Nombre Invalido');
				return false
			}
			for(i=0;i<name.length;i++){
				if ((name[i]>='0') && (name[i]<='9')){
					alert("Nombre Invalido")
					return false
				}
				if ((name[i]==' ') && (i+1<name.length)){
					if (name[i+1]==' '){
						alert("Nombre Invalido: no se permiten dos espacios en blanco seguidos")
						return false
					}
				}
			}
		}	
		if (document.register.username.value!="") {
			var nick=document.register.username.value;
			if (nick.length < 4){
				alert("Apodo demasiado corto")
				return false
			}
			for(i=0;i<nick.length;i++){
				if(' '==nick[i]){
					alert("Apodo debe ser sin espacios")
					return false
				}
			}
		}
		if (document.register.userdni.value=="") {
			alert("Debe indicar su DNI")
			return false
		}else {
			var dni=document.register.userdni.value;
			if (dni.length < 8){
				alert("DNI incorrecto (8 caracteres minimo)")
				return false
			}
			if (isNaN(dni)){
				alert("Número de DNI inválido")
				return false
			}
		}
		if (document.register.password.value=="") {
			alert("Debe indicar su Contraseña")
			return false
		} else {
			var pass=document.register.password.value;
			if (pass.length < 6){
				alert("Password demasiado corta")
				return false
			}		
		}
		if (document.register.password_conf.value=="") {
			alert("Debe confirmar su Contraseña")
			return false
		} else {
			var pass1=document.register.password.value;
			var pass2=document.register.password_conf.value;
			if (pass1 != pass2){
				alert("Password distintas, compruebe su contraseña")
				return false
			}		
		}
		if (document.register.email.value=="") {
			alert("Debe indicar su Email")
			return false
		} else {
			var reg = /^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/;
			var e_mail =document.register.email.value;
			if(reg.test(e_mail) == false) {
				alert('La dirección de email es incorrecta');
				return false
			}
		}
		if (document.register.tlf.value!="") {
			var telef=document.register.tlf.value;
			if (telef.length < 9){
				alert("Telefono incorrecto (9 numeros minimo)")
				return false
			}
			if (isNaN(telef)){
				alert("Telefono inválido (solo numeros)")
				return false
			}
		}
		return true
		}
		
		function validar_DNI(){
		if (document.register.userdni.value=="") {
			alert("Debe indicar su DNI")
			return false
		}else {
			var dni=document.register.userdni.value;
			if (dni.length < 8){
				alert("DNI incorrecto (8 caracteres minimo)")
				return false
			}
			if (isNaN(dni)){
				alert("Número de DNI inválido")
				return false
			}
		}		
		return true
		}	
		
		
		function validar_anadir(){
		if (document.register.titulo.value=="") {
			alert("Debe indicar el Título")
			return false
		}	
		if (document.register.slug.value=="") {
				alert("Debe indicar el slug")
				return false
		}
		if (document.register.director.value=="") {
			alert("Debe indicar el Director")
			return false
		}
		if (document.register.actores.value=="") {
			alert("Debe indicar los actores")
			return false
		}
		if (document.register.titor.value=="") {
			alert("Debe indicar el título original")
			return false
		}
		if (document.register.fecha.value=="") {
			alert("Debe indicar la fecha de estreno")
			return false
		}
		if (document.register.imagenp.value=="") {
			alert("Debe añadir la carátula pequeña")
			return false
		}
		if (document.register.imageng.value=="") {
			alert("Debe añadir la carátula grande")
			return false
		}
		if (document.register.trailer.value=="") {
			alert("Debe indicar el Trailer")
			return false
		}
		return true
		}
	
	</script>