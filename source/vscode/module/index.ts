/// Talos Modules
import { Output } from '@/talos/output';
import { Command } from '@/talos/command';
import { Language } from '@/talos/language';
import { Settings } from '@/talos/settings';
import { Extension } from '@/talos/extension';
import { Inversify, Dependency } from '@/talos/utilities';

/** Core Extension Module */
export const Module = new Inversify.ContainerModule((_) => {
    //  COMMAND BINDINGS  //

    _.bind(Command.Registry).toSelf().inSingletonScope();

    //  EXTENSION BINDINGS  //

    Dependency.couple(_, Extension.Contribution);
    _.bind(Extension.Lifecycle).toSelf().inSingletonScope();
    _.bind(Extension.Service).toService(Extension.Lifecycle);

    //  LANGUAGE BINDINGS  //

    _.bind(Language.Client).toSelf().inSingletonScope();
    _.bind(Language.Contribution).toSelf().inSingletonScope();
    _.bind(Language.Service).toService(Language.Contribution);
    _.bind(Extension.Contribution).toService(Language.Contribution);

    //  OUTPUT BINDINGS  //

    _.bind(Output.Contribution).toSelf().inSingletonScope();
    _.bind(Output.Service).toService(Output.Contribution);

    //  SETTINGS BINDINGS  //

    _.bind(Settings.contribution()).toSelf().inSingletonScope();
    _.bind(Extension.Contribution).toService(Settings.contribution());
});
