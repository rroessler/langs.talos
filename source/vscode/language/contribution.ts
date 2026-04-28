/// Talos Modules
import { Command } from '@/talos/command';
import { Settings } from '@/talos/settings';
import { Extension } from '@/talos/extension';
import { Decorator, Disposable, Inversify } from '@/talos/utilities';

/// Package Modules
import { Client } from './client';
import { Service } from './service';

/** Language Service Contribution. */
@Inversify.injectable()
@Decorator.Class.Rename('Language.Service')
export class Contribution extends Disposable.Registry implements Service, Extension.Contribution {
    //  INJECTABLES  //

    /** Language Client Instance. */
    @Inversify.inject(Client) protected readonly m_client!: Client;

    /** Commands Registry. */
    @Inversify.inject(Command.Registry) protected readonly m_commands!: Command.Registry;

    //  LIFECYCLE METHODS  //

    /** Handles configuring the instance. */
    async configure() {
        // register the base client instance
        this.m_subscribe(this.m_client);

        // handle when the underlying settings change (eg: restart the server instance)
        this.m_subscribe(Settings.listen('server.loggingLevel', () => this.m_client.restart()));
        this.m_subscribe(Settings.listen('server.executablePath', () => this.m_client.restart()));

        // prepare all the necessary event listeners
        this.m_subscribe(this.m_commands.register(Command.Key.RESTART, () => this.m_client.restart()));

        // finally force the client to be initialized first
        await this.m_client.restart();
    }

    //  PUBLIC METHODS  //

    /** Handles restarting the language service. */
    async restart(): Promise<void> {
        return this.m_client.restart();
    }

    /** Makes a client request. */
    async request(...args: any[]) {
        return (<any>this.m_client.request)(...args);
    }

    /** Sends a client notification. */
    async notify(...args: any[]) {
        return (<any>this.m_client.notify)(...args);
    }
}
