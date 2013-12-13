using MVCWithWCFAsModel.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVCWithWCFAsModel.Controllers
{
    public class HomeController : Controller
    {
        ServiceReference1.Service1Client ServiceProxy = new ServiceReference1.Service1Client();
        //
        // GET: /Home/
        public ActionResult Index()
        {
            List<Book> list = JsonConvert.DeserializeObject<List<Book>>(ServiceProxy.getProductsCatalog());
            return View(list);
        }
	}
}