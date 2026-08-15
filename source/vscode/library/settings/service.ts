/// VSC Modules
import { Command } from '@/vscode/command';
import { Extension } from '@/vscode/extension';
import { Decorator, Disposable, Inversify } from '@/vscode/utilities';

/** Settings Service. */
@Inversify.injectable()
@Decorator.Class.Rename('Settings.Service')
export class Service extends Disposable.Registry implements Extension.Plugin {
    //  INJECTABLES  //

    /** Commands Service. */
    @Inversify.inject(Command.Service) protected readonly m_commands!: Command.Service;

    //  LIFECYCLE METHODS  //

    /** Handles configuring the service. */
    async configure() {
        this.m_subscribe(this.m_commands.register(Command.Key.SETTINGS, open));
    }
}
