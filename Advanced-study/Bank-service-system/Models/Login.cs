using System.ComponentModel.DataAnnotations;

namespace Bank_service_system.Models
{
    public class Login
    {
        [Required]
        public string username { get; set; }
        [Required]
        public string passworld { get; set; }
    }
}
