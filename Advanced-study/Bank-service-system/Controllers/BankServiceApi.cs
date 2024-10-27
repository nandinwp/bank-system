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
            if (login == null) { return BadRequest("error"); }

            if (ModelState.IsValid) 
                if(login.username.Equals("guest") && login.passworld.Equals("1234"))
                    return Ok("autorizado");
                else
                    return Unauthorized("Não autorizado");
            else
                return NotFound("");
        }

    }
}
