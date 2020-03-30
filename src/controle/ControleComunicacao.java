/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import br.pro.turing.javino.Javino;
import modelo.Programacao;
import org.json.JSONObject;

/**
 *
 * @author Vitor
 */
public class ControleComunicacao {

    Javino comunica = new Javino();
    JSONObject json = new JSONObject();

    public boolean confirmaConexao(String porta) {

        boolean confirmacao = false;

        confirmacao = this.comunica.sendCommand(porta, "confirma_conexao");

        return confirmacao;
    }

    public boolean enviaProg(String porta, Programacao prog) {
        boolean confirmacao = false;
        boolean envioStatus = false;
        boolean envioProg = false;

        
        confirmacao = confirmaConexao(porta);

        if (confirmacao) {

            // Envia Status    
            envioStatus = comunica.sendCommand(porta, prog.getStatus().toString());

            // Envia Prog
            comunica.sendCommand(porta, prog.getParametros().toString());
        }
        confirmacao = false;
        if (envioProg && envioStatus) {
            confirmacao = true;
        }

        return confirmacao;
    }

public int varreSaidas(String[] portas){
int porta = -1;
boolean confirma = false;

  for(int i = 0; i<portas.length; i++){
        confirma = comunica.sendCommand(portas[i], "testePorta");
        if(confirma){
            porta = i;
        }
  }

return porta;
}
}