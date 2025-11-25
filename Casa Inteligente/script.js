// ### CONFIGURANDO O BROKEN MQTT PARA O NAVEGADOR
const MQTT_URL ="wss://test.mosquitto.org:8081";

// ### CONFIGURANDO O ID DO CLIENTE MQTT
const clienteId = 'web-casa-inteligente-breno';

// ### CRIANDO O CLIENTE MQTT DO NAVEGADOR, POREM AINDA NÃO ESTAMOS CONECTADOS AO BROKEN
// const cliente = mqtt.connect(MQTT_URL, {
//     clienteId,
//     clean: true,
//     connectTimeout: 4000,
// });

// ### VARIAVEIS DOS DISPOSITIVOS
const lampSalaInput = document.getElementById("lamp-sala");
const lampSalaTexto = document.getElementById("lamp-sala-texto")

// ### ALTERANDO ESTADOS DOS DISPOSITIVOS
// PEGANDO EVENTO DE MUDAÇA DO BOTÃO (LIGADO/DESLIGADO)

// CONTROLE DA SALA 
lampSalaInput.addEventListener("change", () => {
    const ligadolampS = lampSalaInput.checked === true;

    if (ligadolampS === true){ 
        console.log("Lâmpada ligada");
        lampSalaTexto.innerHTML = "Ligada";
    } else {
        console.log("Lâmpada desligada");
        lampSalaTexto.innerHTML = "Desligada"
    }
});


const cortSalaInput = document.getElementById("cort-sala")
const cortSalaTexto = document.getElementById("cort-sala-texto")

cortSalaInput.addEventListener("change", () => {
    const ligadocortS = cortSalaInput.checked === true;

    if (ligadocortS === true){ 
        console.log("Cortina aberta");
        cortSalaTexto.innerHTML = "Aberta";
    } else {
        console.log("Cortina fechada");
        cortSalaTexto.innerHTML = "Fechada"
    }
});


const portSalaInput = document.getElementById("port-sala")
const portSalaTexto = document.getElementById("port-sala-texto")

portSalaInput.addEventListener("change", () => {
    const ligadoportS = portSalaInput.checked === true;

    if (ligadoportS === true){ 
        console.log("Porta aberta");
        portSalaTexto.innerHTML = "Aberta";
    } else {
        console.log("Porta fechada");
        portSalaTexto.innerHTML = "Fechada"
    }
});

// CONTROLE DA COZINHA
const lampCozinhaInput = document.getElementById("lamp-cozinha")
const lampCozinhaTexto = document.getElementById("lamp-cozinha-texto")

lampCozinhaInput.addEventListener("change", () => {
    const ligadolampC = lampCozinhaInput.checked === true;

    if (ligadolampC === true){ 
        console.log("Lâmpada ligada");
        lampCozinhaTexto.innerHTML = "Ligada";
    } else {
        console.log("Lâmpada fechada");
        lampCozinhaTexto.innerHTML = "Desligada"
    }
});


const exausCozinhaInput = document.getElementById("exaus-cozinha")
const exausCozinhaTexto = document.getElementById("exaus-cozinha-texto")

exausCozinhaInput.addEventListener("change", () => {
    const ligadoexausC = exausCozinhaInput.checked === true;

    if (ligadoexausC === true){ 
        console.log("Exaustor ligado");
        exausCozinhaTexto.innerHTML = "Ligado";
    } else {
        console.log("Exaustor desligado");
        exausCozinhaTexto.innerHTML = "Desligado"
    }
});


// CONTROLE DA VARANDA/COZINHA
const lampVarandaInput = document.getElementById("lamp-varanda")
const lampVarandaTexto = document.getElementById("lamp-varanda-texto")

lampVarandaInput .addEventListener("change", () => {
    const ligadolampV = lampVarandaInput .checked === true;

    if (ligadolampV === true){ 
        console.log("Lâmpada ligada");
        lampVarandaTexto.innerHTML = "Ligada";
    } else {
        console.log("Lâmpada desligada");
        lampVarandaTexto.innerHTML = "Desligada"
    }
});

const varVarandaInput = document.getElementById("var-varanda")
const varVarandaTexto = document.getElementById("var-varanda-texto")

varVarandaInput.addEventListener("change", () => {
    const ligadovarV = varVarandaInput.checked === true;

    if (ligadovarV === true){ 
        console.log("Varanda aberta");
        varVarandaTexto.innerHTML = "Aberta";
    } else {
        console.log("Varanda Fechada");
        varVarandaTexto.innerHTML = "Fechada"
    }
});


const portGaragemInput = document.getElementById("port-garagem")
const portGaragemTexto = document.getElementById("port-garagem-texto")

portGaragemInput.addEventListener("change", () => {
    const ligadoportG = portGaragemInput.checked === true;

    if (ligadoportG === true){ 
        console.log("Portão aberto");
        portGaragemTexto.innerHTML = "Aberto";
    } else {
        console.log("Portão fechado");
        portGaragemTexto.innerHTML = "Fechado"
    }
});


const irVarandaInput = document.getElementById("ir-varanda")
const irVarandaTexto = document.getElementById("ir-varanda-texto")

irVarandaInput.addEventListener("change", () => {
    const ligadoirV = irVarandaInput.checked === true;

    if (ligadoirV === true){ 
        console.log("Irrigação ligada");
        irVarandaTexto.innerHTML = "ligada";
    } else {
        console.log("Irrigação desligada");
        irVarandaTexto.innerHTML = "desligada"
    }
});


// ### CHAMANDO UM EVENTO DO JS DO TIPO "DOMContentLoaded", QUE É O EVENTO QUE ACONTECE,
// ### APÓS TODA A MINHA PÁGINA DE HTML SER CARREGADA. 
// document.addEventListener("DOMContentLoaded", () => {
//     console.log("Página carregada com sucesso ✅;.. Conectando ao Mosquitto!");
// });

// //  ### ESTABELECENDO A CONEXÃO COM O BROKEN MQTT
// cliente.on("connect", () => {
//     console.log("Conexão etabelecida com Sucesso ✅!");
//     console.log("Cliente conectado: ", clienteId);

// // ### CRIANDO UM TOPICO PARA ACESSAR MENSAGENS DO MQTT
// const topicoTeste = 'teste/Breno'

// // ### RECEBENDO MENSAGENS DE ERRO CASO ALGO ACONTEÇA
// cliente.subscribe(topicoTeste);

// // ### PREPARANDO MENSAGEM DE ERRO CASO ALGO ACONTEÇA
// cliente.on("error", (erro) => {
//     console.log("Erro ao conectar ao Broken MQTT 🚨!");
//     console.log(erro);    
// });

// // ### RECEBENDO AS MENSAGEM DOS TÓPICOS ASSINADOS NO MQTT PELO CLIENTE
// cliente.on("message", (topico, mensagem) => {
//     console.log("Topico recebido: ", topico);
//     console.log("Mensagem recebida: ", mensagem);
// });
// });