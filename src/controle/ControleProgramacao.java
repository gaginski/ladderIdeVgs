/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.JLabel;
import modelo.Programacao;
import modelo.Configuracoes;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.simple.parser.ParseException;

/**
 *
 * @author Vitor
 */
public class ControleProgramacao {

    Programacao prog = new Programacao();
    
    String stringComandos = "";

    public String organizaComandosExibicao(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws JSONException, IOException, UnknownHostException, FileNotFoundException, ParseException {

        organizaComandosEnvio(linhas, colunas, lComandos, lLinhas);

        return stringComandos;
    }

    public Programacao organizaComandosEnvio(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws JSONException, IOException, UnknownHostException, FileNotFoundException, ParseException {
        // declara variveis 
        int[][][] matrizComandos = new int[linhas][colunas][5];
        JSONObject jsonEntrada = new JSONObject(), jsonComandos = new JSONObject(), jsonSaida = new JSONObject(), jsonAux = new JSONObject();
        String entradas = null, saidas = null, progNewFormat = "";

        // captura status no objeto prog
        

        //percorre todos as labels comparando o icone com os comandos, salvando na matriz os as informações de comandos setados
        for (int i = 0; i < linhas; i++) {
            for (int c = 0; c < colunas; c++) {
                for (int a = 0; a < lComandos.length; a++) {
                    if (lLinhas[i][c].getIcon().equals(lComandos[a].getIcon())) {
                        matrizComandos[i][c][0] = 1; // confirmaConteudo
                        matrizComandos[i][c][1] = i; // Linha
                        matrizComandos[i][c][2] = c; // Coluna
                        matrizComandos[i][c][3] = a; // Comando
                        matrizComandos[i][c][4] = Integer.parseInt(lLinhas[i][c].getText()); // Porta

                    }
                }
            }
        }

        // percorre toda a matriz int  preenchida, gerando o json
        for (int i = 0; i < linhas; i++) {
            int contE = 0;
            int contS = 0;
            stringComandos = stringComandos + ("Linha_" + i + ": {");
            entradas = "\n   Entrada{ ";
            saidas = "\n   Saídas{ ";
            progNewFormat = progNewFormat.concat("L"+(i+1)+"-");
            for (int c = 0; c < colunas; c++) {
                if (matrizComandos[i][c][0] == 1) {

                    switch (matrizComandos[i][c][3]) {
                        case (0):
                        case (1):
                        case (2):
                        case (3):
                            jsonEntrada.put("Cm" + contE, matrizComandos[i][c][3] + ", " + matrizComandos[i][c][4]);
                            entradas = entradas + "\n       Comando:" + matrizComandos[i][c][3]
                                    + ", Porta:" + matrizComandos[i][c][4];
                            contE++;
                            progNewFormat = progNewFormat.concat("I"+matrizComandos[i][c][3]+"P"+matrizComandos[i][c][4]+"-");
                            break;
                        case (4):
                        case (5):
                        case (6):
                        case (7):
                            jsonSaida.put("Cm" + contS, matrizComandos[i][c][3] + ", " + matrizComandos[i][c][4]);
                            saidas = saidas + "\n       Comando:" + matrizComandos[i][c][3]
                                    + ", Porta:" + matrizComandos[i][c][4];
                            progNewFormat = progNewFormat.concat("O"+matrizComandos[i][c][3]+"P"+matrizComandos[i][c][4]+"-");
                            contS++;
                            break;
                        default:
                            break;
                    }

                } else{
                    progNewFormat = progNewFormat.concat("0-");
                }
            }
            entradas = entradas + "}";
            saidas = saidas + "}";
            stringComandos = stringComandos + entradas + saidas + "\n   }\n";
            jsonAux.put("In", jsonEntrada);
            jsonAux.put("Out", jsonSaida);
            jsonComandos.put("Ln" + i, jsonAux);
            jsonAux = new JSONObject();
            jsonEntrada = new JSONObject();
            jsonSaida = new JSONObject();

        }

        prog.parametros = jsonComandos;
        prog.progNewFormat = progNewFormat;

        return prog;
    }

    public Programacao organizaPacotes(Programacao p) {

        String aux = null;
        int cont, tamanhoVetor = p.progNewFormat.length();

        aux = p.progNewFormat;

        cont = (int) Math.floor(tamanhoVetor / 240) + 1;

        String[] pacotes = new String[cont];

        for (int i = 0; i < cont; i++) {
            if (i == cont - 1) {
                pacotes[i] = aux.substring(i * 220, aux.length());
            } else {
                pacotes[i] = aux.substring(i * 220, (i * 220) + 220);
            }
        }

        p.pacotes = pacotes;

        return p;
    }

    public JSONObject iniciaProg() throws JSONException, UnknownHostException, IOException, FileNotFoundException, ParseException {
        controleConfiguracao controleArquivo = new controleConfiguracao();
        JSONObject status = new JSONObject();
        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        Date date = new Date();
        Configuracoes config  = new Configuracoes();
      
        
        config = controleArquivo.configuracao();

        status.put("DataHoraCarregamento", dateFormat.format(date));
        status.put("Pc_Carregou", InetAddress.getLocalHost().getHostName());
        status.put("IP_carregou", InetAddress.getLocalHost().getAddress());
        status.put("Porta", config.porta);

        System.out.println("Json Status Criado");
        return status;

    }

}
