// See https://aka.ms/new-console-template for more information

using DryIoc;
using RGU.Magisters.Dev;

DryIoc.IContainer container = new Container();
container.Register<ICpu, RyzenCpu>();
//container.Register<IGpu, NVidiaGpu>();
//container.RegisterDelegate(() => default(IGpu));
container.RegisterInstance(default(IGpu));
container.Register<IRam, SamsungRam>();
container.Register<IOperatingSystem, FedoraLinuxOS>();
container.Register<ICompukter, Compukter>();
// TODO:
container.RegisterMany<Wtf>();
container.RegisterMapping<ICpu, IGpu>();
//

var cpu = container.Resolve<ICompukter>(IfUnresolved.ReturnDefault);
var x = 10;
