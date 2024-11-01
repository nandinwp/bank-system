using Bank_service_system.Models;
using Microsoft.AspNetCore.Mvc;

namespace Bank_service_system.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BankServiceApi : ControllerBase
    {
        [HttpPost]
        [Route("login")]
        public async Task<IActionResult> LoginAction([FromBody] Login login)
        {
            return login == null ? 
                BadRequest("error") :
                ModelState.IsValid ?
                login.username.Equals("guest") && login.username.Equals("1234") ?
                Ok("autorizado") :
                Unauthorized("Não autorizado") : 
                NotFound("Não encontrado");
        }

    }
}
