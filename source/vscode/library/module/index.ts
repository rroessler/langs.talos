/// VSC Modules
import { Output } from '@/vscode/output';
import { Command } from '@/vscode/command';
import { Language } from '@/vscode/language';
import { Settings } from '@/vscode/settings';
import { Extension } from '@/vscode/extension';
import { Dependency, Inversify } from '@/vscode/utilities';

/** Core Extension Module */
export const Module = new Inversify.ContainerModule((_) => {
    //  BASELINE BINDINGS  //

    Dependency.couple(_, Extension.Plugin);

    //  COMMAND BINDINGS  //

    _.bind(Command.Service).toSelf().inSingletonScope();
    _.bind(Extension.Plugin).toService(Command.Service);

    //  EXTENSION BINDINGS  //

    _.bind(Extension.Lifecycle).toSelf().inSingletonScope();
    _.bind(Extension.Service).toService(Extension.Lifecycle);

    //  LANGUAGE BINDINGS  //

    _.bind(Language.Client).toSelf().inSingletonScope();
    _.bind(Language.Service).toSelf().inSingletonScope();
    _.bind(Extension.Plugin).toService(Language.Service);

    //  OUTPUT BINDINGS  //

    _.bind(Output.Service).toSelf().inSingletonScope();
    _.bind(Extension.Plugin).toService(Output.Service);

    //  SETTINGS BINDINGS  //

    _.bind(Settings.Service).toSelf().inSingletonScope();
    _.bind(Extension.Plugin).toService(Settings.Service);
});
